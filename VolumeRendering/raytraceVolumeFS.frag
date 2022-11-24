#version 330

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
	vec4 start;
	vec4 dir;
};


/*uniform struct {
	vec3 volumeDimension;
	vec3 position[MAX_DIM * MAX_DIM * MAX_DIM];
	vec3 texCoords[MAX_DIM * MAX_DIM * MAX_DIM];
}volumeData;*/

uniform vec3 cameraPos;
uniform sampler3D brainTexture;

in vec4 rayDir;

out vec4 fragmentColor;

float solveQuadratic(float a, float b, float c){
	
	float disc = b * b - 4.0f * a * c;
	
	if (disc < 0.0f){
		return -1;
	}

	float t0 = (-b - sqrt(disc)) / (2.0 * a);
	float t1 = (-b + sqrt(disc)) / (2.0 * a);
	
	return (t1<0.0) ? t0 : (t0<0.0 ? t1 : min(t1, t0));;
}

float intersect(Metaball metaball, Ray ray){
	
	vec4 L = ray.start - vec4(metaball.center, 1.0f);
	
	float a = dot(ray.dir, ray.dir);
	float b = 2.0f * dot(L, ray.dir);
	float c = dot(L, L) - pow(metaball.radius, 2.0f);
	
	float t = solveQuadratic(a, b, c);
	return t;
}

vec3 shade(vec3 normal, vec3 color){
	float refl = -max(dot(rayDir.xyz, normal), 0);
	return color * refl;
}

void main(){
	Metaball metaball1;
	Metaball metaball2;

	Ray ray;
	ray.dir = vec4(rayDir.xyz, 0.0f);
	ray.start = vec4(cameraPos, 1.0f);

	metaball1.center = vec3(-5.0f, 0.0f, 0.0f);
	metaball1.radius = 0.5f;

	metaball2.center = vec3(-6.0f, 0.0f, 0.0f);
	metaball2.radius = 0.5f;	

	float t = intersect(metaball1, ray);
	if (t > 0.0f){
		vec4 hit = ray.start + t * ray.dir;
		vec3 normal = normalize((hit - vec4(metaball1.center, 1.0f)).xyz);
		fragmentColor = vec4(normal.xyz, 1.0f);
	}

	else{
		fragmentColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	}
}

/*
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

float manhattanDistance(vec3 x, vec3 y) {
	return dot(x - y, x - y);
}

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


//Blinn metaball
float blinnMetaball(float r){
	if (r == 0.0f)
		r = 0.001;
	return 1.0f/(r * r);
}

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
float wyvillMetaball(float distance, float radius){
	if (distance > pow(radius, 2)){
		return 0.0f;
	}

	float fi = 1.0f - 3 * distance / pow(radius, 2) + 3 * pow(distance, 2) / pow(radius, 4) - pow(distance, 3) / pow(radius, 6);
	return fi;
}

float wyvillMetaballScene(vec3 p, int metaballSize, Metaball metaballs[MAX_METABALL], out vec3 color){
	float fSum = 0.0f;
	for (int i = 0; i < metaballSize; i++){
		float distance = manhattanDistance(p, metaballs[i].center);
		float f = wyvillMetaball(distance, metaballs[i].radius);
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

void generateMetaballs(ivec3 dimension, out Metaball metaballs[MAX_METABALL]) {
	for (int i = 0; i < dimension.x; i++) {
		for (int j = 0; j < dimension.y; j++) {
			for (int k = 0; k< dimension.z; k++) {

				metaballs[i*dimension.y*dimension.z + j * dimension.z + k].radius = 0.25f;
				vec3 position = vec3(-i, -j, -k) / dimension;
				metaballs[i*dimension.y*dimension.z + j * dimension.z + k].center = position;
				metaballs[i*dimension.y*dimension.z + j * dimension.z + k].color = abs(position);
			}
		}
	}
}

float solveQuadratic(float a, float b, float c){
	
	float disc = b * b - 4.0f * a * c;
	
	if (disc < 0.0f){
		return -1;
	}

	float t0 = (-b - sqrt(disc)) / (2.0 * a);
	
	return t0;
}

float intersect(Metaball metaball, Ray ray){
	
	vec3 L = ray.start - metaball.center;
	
	float a = dot(ray.dir, ray.dir);
	float b = 2.0f * dot(L, ray.dir);
	float c = dot(L, L) - pow(metaball.radius + 2.0f, 2.0f);
	
	float t = solveQuadratic(a, b, c);
	return t;
}

float sortMetaballs(Ray ray, in Metaball allMetaballs[MAX_METABALL], out int intersectedSize, out Metaball intersectedMetaballs[MAX_METABALL]) {
	float t = -1.0f;
	for (int i = 0; i<allMetaballs.length(); i++) {
		float currentT = intersect(allMetaballs[i], ray);
		if (t > currentT || t == -1.0f) {
			t = currentT;
		}
	}
	vec3 hit = ray.start + t * ray.dir;
	intersectedSize = 0;
	for (int i = 0; i<allMetaballs.length(); i++) {
		float distance = manhattanDistance(hit, allMetaballs[i].center);
		if (distance < pow(allMetaballs[i].radius + 2.0f, 2)) {
			intersectedMetaballs[intersectedSize] = allMetaballs[i];
			intersectedSize++;
		}
	}
	return t;
}

void main(){
	//setup ray
	Ray ray;
	ray.dir = normalize(rayDir.xyz);
	ray.start = cameraPos;
	
	//setup metaballs
	Metaball metaballs[MAX_METABALL];
	Metaball intersectedMetaballs[MAX_METABALL];
	//IF THE DIMENSION CHANGES THEN UPDATE THE MAX_METABALL MACRO
	ivec3 dimension = ivec3(6, 6, 6);
	generateMetaballs(dimension, metaballs);
	int intersectedMetaballSize = 0;
	float t = sortMetaballs(ray, metaballs, intersectedMetaballSize, intersectedMetaballs);

	//setup raymarch
	float t1 = (t - cameraPos.z) / ray.dir.z;
	float t2 = (t - cameraPos.z) / ray.dir.z;
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
		if (wyvillMetaballScene(p, intersectedMetaballSize, intersectedMetaballs, color) > 0.0f){
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
		fragmentColor = vec4(0.1f, 0.1f, 0.1f, 1.0f);
	}
}

*/
