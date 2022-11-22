#version 430

layout(location = 0) in vec4 vertexPosition;

uniform mat4 viewProjMatrix;

void main(){
	gl_Position = vertexPosition * viewProjMatrix;
}