#version 330
precision highp float;

struct Ray {
	vec3 start;
	vec3 dir;
};

struct Cube{
	vec3 size;
	vec3 position;
};

uniform vec3 cameraPos;
uniform sampler3D brainTexture;
uniform float minStep;
uniform float treshold;

in vec4 rayDir;

out vec4 fragmentColor;

float raymarchCube(vec3 p, Cube cube){
	float d =  length(max(abs(p - cube.position) - cube.size, 0.0f));
	return d;
}

vec3 fGrad(vec3 p, Cube cube){
  vec3 normal = vec3(
  raymarchCube(p + vec3(+0.05, 0.0, 0.0), cube ) -
  raymarchCube(p + vec3(-0.05, 0.0, 0.0), cube ) ,
  raymarchCube(p + vec3(0.0, +0.05, 0.0), cube ) -
  raymarchCube(p + vec3(0.0, -0.05, 0.0), cube ) ,
  raymarchCube(p + vec3(0.0, 0.0, +0.05), cube ) -
  raymarchCube(p + vec3(0.0, 0.0, -0.05), cube )
  );

  return normalize(normal);
}

void main(){
	//setup ray
	Ray ray;
	ray.dir = normalize(rayDir.xyz);
	ray.start = cameraPos;

	//setup cube
	Cube cube;
	cube.position = vec3(0.5f, 0.5f, 0.5f);
	cube.size = vec3(0.45f, 0.45f, 0.45f);

	//setup raymarch
	float t1 = (5.0 - cameraPos.z) / ray.dir.z;
	float t2 = (-5.0 - cameraPos.z) / ray.dir.z;
	float tStart = max(min(t1, t2), 0.0f);
	float tEnd = max(max(t1, t2), 0.0f);
	int nSteps = 5800;

	vec3 p = ray.start + ray.dir * tStart;
	bool found = false;
	float h = 1.0f;
	vec4 color;

	vec3 step = ray.dir * min((tEnd-tStart)/float(nSteps), minStep);
	for (int i = 0; i < nSteps; i++){

		if (raymarchCube(p, cube) < 0.1f){
			h = texture(brainTexture, p).r;
			if (h > treshold){
				found = true;
				color += vec4(h, h, h, 1.0f);
				break;
			}
			found = true;
		}
		p = p + step;
	}

	if (found){
		fragmentColor = color;
	}
	else{
		fragmentColor = vec4(0.2f, 0.2f, 0.2f, 1.0f);
	}
}
