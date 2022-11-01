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
