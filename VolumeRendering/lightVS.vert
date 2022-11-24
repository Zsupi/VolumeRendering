#version 330

layout(location = 0) in vec3 vertexPosition;

uniform mat4 modellMatrix;
uniform mat4 viewProjMatrix;

void main(){
	gl_Position = vec4(vertexPosition, 1.0f) * modellMatrix * viewProjMatrix;
}