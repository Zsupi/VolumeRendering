#version 330

layout(location = 0) in vec4 vertexPosition;
layout(location = 1) in vec3 vertexNormal;
layout(location = 2) in vec2 texCoord; 

uniform mat4 modellMatrix;
uniform mat4 viewProjMatrix;

out struct{
	vec3 normal;
	vec3 position;
	vec2 texCoord;
}VSO;


void main(){
	mat4 invModellMatrix = inverse(modellMatrix);
	VSO.normal = (invModellMatrix * vec4(vertexNormal, 0.0f)).xyz;
	VSO.position = (vertexPosition * modellMatrix).xyz;
	VSO.texCoord = texCoord;
	gl_Position = vertexPosition * modellMatrix * viewProjMatrix;
}