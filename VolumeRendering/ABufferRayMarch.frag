#version 430
precision highp float;

struct Metaball{
	vec3 center;
	float radius;
	vec3 color;
};

struct Ray {
	vec3 start;
	vec3 dir;
};

struct Screen {
    uint pixel;
    float padding[3];
};

struct LinkedListElement {
    uvec2 element;
    float padding[2];
};

// holds the positions of the metaballs
layout(std430, binding = 1) buffer positionBuffer {
    vec4 position[];
};

// holds the index of the first element of the linked list
layout(std430, binding = 2) buffer screenBuffer {
    Screen screen[];
};

// element.x stands for the index of the previous element
// element.y stands for the metaballId
layout(std430, binding = 3) buffer linkedListBuffer {
    LinkedListElement element[];
};

uniform vec3 cameraPos;
uniform float minStep;
uniform sampler3D volumeData;

// holds the size of the window
uniform uvec2 windowSize; 

// holds the direction of the ray
in vec4 rayDir;

out vec4 fragmentColor;

Metaball createMetaball(vec4 position) {
	Metaball metaball;
	metaball.center = position.xyz;
	metaball.radius = 0.12f;
	//metaball.color = abs(position.xyz);
	metaball.color = texture(volumeData, position.xyz).rrr;
	return metaball;
}

//Wyvill Metaball
float wyvillMetaball(float distance, float radius) {
	if (distance > pow(radius, 2)){
		return 0.0f;
	}

	float fi = 1.0f - 3 * distance / pow(radius, 2) + 3 * pow(distance, 2) / pow(radius, 4) - pow(distance, 3) / pow(radius, 6);
	return fi;
}

float wyvillMetaballTest(vec3 p, vec4 metaballCenter, out vec3 color) {
	Metaball metaball = createMetaball(metaballCenter);

	float mannhattanistance = dot(p - metaball.center, p - metaball.center);
	float f = wyvillMetaball(mannhattanistance, metaball.radius);
	color += f * metaball.color;
	return f;
}

float sdSphere( vec3 p, vec3 center, float r )
{
  return length(p-center)-r;
}

float ABuffer_WyvillMetaballScene(vec3 p, out vec3 color, out float safeDistance) {
	float fSum = 0.0f;
	uint pixelId = uint(gl_FragCoord.y) * (windowSize.x-1) + uint(gl_FragCoord.x);

	uint pixelValue = screen[pixelId].pixel;
	while(pixelValue != 0) {
		uvec2 currentElement = element[pixelValue].element;
		pixelValue = currentElement.x;
		uint metaballId = currentElement.y;
		vec4 metaballCenter = position[metaballId];

		float tmpDistance = sdSphere(p, metaballCenter.xyz, 0.2f);
		if (tmpDistance < safeDistance || safeDistance == -1.0f) {
			safeDistance = tmpDistance;
		}

		float f = wyvillMetaballTest(p, metaballCenter, color);
		fSum += f;
	}
	const float A = 0.7f;
	return -A + fSum;
}

void main(){
	//setup ray
	Ray ray;
	ray.dir = normalize(rayDir.xyz);
	ray.start = cameraPos;

	//setup raymarch
	float t1 = (10.0f - cameraPos.z) / ray.dir.z;
	float t2 = (-10.0f - cameraPos.z) / ray.dir.z;
	float tStart = max(min(t1, t2), 0.0);
	float tEnd = max(max(t1, t2), 0.0);
	int nSteps = 100;

	vec3 p = ray.start + ray.dir * tStart;
	bool found = false;
	vec3 color;

	//raymarch

	float d = -1.0f;
	for (int i = 0; i < nSteps; i++){
		if (ABuffer_WyvillMetaballScene(p, color, d) > 0.0f){
			found = true;
			break;
		}
		p = p + ray.dir * max(d, minStep);
	}

	if (found){
		fragmentColor = vec4(color, 1.0f);
	}
	else{
		fragmentColor = vec4(0.1, 0.1f, 0.1f, 1.0f);
	}
}
