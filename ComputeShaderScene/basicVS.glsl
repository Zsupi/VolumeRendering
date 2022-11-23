#version 430

layout(location = 0) in vec4 vertexPosition;

uniform mat4 viewProjMatrix;
uniform mat4 modelMatrix;

void main(){
	gl_Position = vertexPosition * modelMatrix * viewProjMatrix;
}