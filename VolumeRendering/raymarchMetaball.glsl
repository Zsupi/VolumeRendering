#version 330
#define MAX_METABALL 64
precision highp float;

struct Metaball{
	vec3 center;
	float radius;
};

struct Hit {
	float t;
	vec3 position;
	vec3 normal;
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

float wyvillMetaball(float r){
	if (r > 1.0f){
		return 0.0f;
	}

	float fi = 1.0f - (4.0f / 9.0f) * pow(r, 6) + (17.0f / 9.0f) * pow(r, 4) - (22.0f / 9.0f) * pow(r, 2);
	return fi;
}

float blinnMetaball(float r){
	if (r == 0.0f)
		r = 0.001;
	return 1.0f/(r * r);
}

float rayMarchMetaballScene(vec3 p, Metaball metaballs[MAX_METABALL]){
	float fSum = 0.0f;
	for (int i = 0; i < metaballs.length(); i++){
		float r = length(p - metaballs[i].center) / metaballs[i].radius;
		//Blinn metaball
		fSum += blinnMetaball(r);
	}

	const float A = 20.0f;

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
	uvec3 dimension = uvec3(4, 4, 4);
	for (int i = 0; i < dimension.x; i++){
		for (int j = 0; j < dimension.y; j++){
			for (int k = 0; k< dimension.z; k++){

				metaballs[i*dimension.y*dimension.z + j * dimension.z + k].radius = (1.0f / dimension.x);
				metaballs[i*dimension.y*dimension.z + j * dimension.z + k].center = vec3(-i, -j, -k) / dimension;

			}
		}
	}

	//setup raymarch
	float t1 = (10.0f - cameraPos.y) / ray.dir.y;
	float t2 = (-10.0f - cameraPos.y) / ray.dir.y;
	float tStart = max(min(t1, t2), 0.0);
	float tEnd = max(max(t1, t2), 0.0);
	int nSteps = 100;

	vec3 p = ray.start + ray.dir * tStart;
	bool found = false;

	vec3 step = ray.dir * min((tEnd-tStart)/float(nSteps), minStep);
	for (int i = 0; i < nSteps; i++){

		if (rayMarchMetaballScene(p, metaballs) > 0.0f){
			found = true;
			break;
		}
		p = p + step;
	}

	if (found){
		fragmentColor = vec4(0.0f, 0.97f, 0.97f, 1.0f);
		fragmentColor = vec4(fGrad(p, metaballs[0]), 1.0f);
	}
	else{
		fragmentColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	}
}
