#version 330
#define MAX_METABALL 216
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

uniform vec3 cameraPos;
uniform float minStep;

in vec4 rayDir;

out vec4 fragmentColor;

float distanceFromMetaball(vec3 p, Metaball metaball){
	return length(p - metaball.center) - metaball.radius;
}

float rayMarchScene(vec3 p, Metaball metaballs[MAX_METABALL]){
	float minDistance = distanceFromMetaball(p, metaballs[0]);

	for (int i = 1; i < metaballs.length(); i++){
		float currentDistance = distanceFromMetaball(p, metaballs[i]);
		minDistance = currentDistance < minDistance ? currentDistance : minDistance;
	}

	return minDistance;
}

float wyvillMetaball(float distance, float radius){
	if (distance > radius){
		return 0.001f;
	}

	float fi = 1.0f - 3 * pow(distance / radius, 2) + 3 * pow(distance / radius, 4) - pow(distance / radius, 6);
	return fi;
}

float blinnMetaball(float r){
	if (r == 0.0f)
		r = 0.001;
	return 1.0f/(r * r);
}

//Blinn metaball
float blinnMetaballScene(vec3 p, Metaball metaballs[MAX_METABALL], out vec3 color){
	float fSum = 0.0f;
	for (int i = 0; i < metaballs.length(); i++){
		float r = length(p - metaballs[i].center) / metaballs[i].radius;
		float f = blinnMetaball(r);
		color += f * metaballs[i].color;
		fSum += f;
	}

	const float A = 500.0f;
	color = color / fSum;
	return -A + fSum;
}

//Wyvill Metaball
float wyvillMetaballScene(vec3 p, Metaball metaballs[MAX_METABALL], out vec3 color){
	float fSum = 0.0f;
	for (int i = 0; i < metaballs.length(); i++){
		float euclidesDistance = (pow(p.x - metaballs[i].center.x, 2) + pow(p.y - metaballs[i].center.y, 2)) / pow(metaballs[i].radius, 4);
		//float r = length(p - metaballs[i].center) / metaballs[i].radius;
		float f = wyvillMetaball(euclidesDistance, metaballs[i].radius);
		color += f * metaballs[i].color * 0.1f;
		fSum += f;
	}

	const float A = 1.5f;
	return -A + fSum;
}

vec3 fGrad(vec3 p, Metaball metaball){
  vec3 normal = vec3(
  distanceFromMetaball(p + vec3(+0.05, 0.0, 0.0), metaball ) -
  distanceFromMetaball(p + vec3(-0.05, 0.0, 0.0), metaball ) ,
  distanceFromMetaball(p + vec3(0.0, +0.05, 0.0), metaball ) -
  distanceFromMetaball(p + vec3(0.0, -0.05, 0.0), metaball ) ,
  distanceFromMetaball(p + vec3(0.0, 0.0, +0.05), metaball ) -
  distanceFromMetaball(p + vec3(0.0, 0.0, -0.05), metaball )
  );

  return normalize(normal);
}

void main(){
	//setup ray
	Ray ray;
	ray.dir = normalize(rayDir.xyz);
	ray.start = cameraPos;
	
	//setup metaballs
	Metaball metaballs[MAX_METABALL];

	//IF THE DIMENSION CHANGES THEN UPDATE THE MAX_METABALL MACRO
	ivec3 dimension = ivec3(6, 6, 6);
	for (int i = 0; i < dimension.x; i++){
		for (int j = 0; j < dimension.y; j++){
			for (int k = 0; k< dimension.z; k++){

				metaballs[i*dimension.y*dimension.z + j * dimension.z + k].radius = 0.6f;
				vec3 position = vec3(-i, -j, -k) / dimension;
				metaballs[i*dimension.y*dimension.z + j * dimension.z + k].center = position;
				metaballs[i*dimension.y*dimension.z + j * dimension.z + k].color = abs(position);

			}
		}
	}

	//setup raymarch
	float t1 = (10.0f - cameraPos.z) / ray.dir.z;
	float t2 = (-10.0f - cameraPos.z) / ray.dir.z;
	float tStart = max(min(t1, t2), 0.0);
	float tEnd = max(max(t1, t2), 0.0);
	int nSteps = 100;

	vec3 p = ray.start + ray.dir * tStart;
	bool found = false;
	vec3 color;
	vec3 step = ray.dir * min((tEnd-tStart)/float(nSteps), minStep);
	for (int i = 0; i < nSteps; i++){

//		if (blinnMetaballScene(p, metaballs, color) > 0.0f){
//			found = true;
//			break;
//		}
		if (wyvillMetaballScene(p, metaballs, color) > 0.0f){
			found = true;
			break;
		}
		p = p + step;
	}

	if (found){
		//fragmentColor = vec4(0.0f, 0.97f, 0.97f, 1.0f);
		//fragmentColor = vec4(fGrad(p, metaballs[0]), 1.0f);
		fragmentColor = vec4(color, 1.0f);
	}
	else{
		fragmentColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	}
}
