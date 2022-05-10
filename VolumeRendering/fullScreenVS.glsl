#version 330

layout(location = 0) in vec4 vertexPosition;

uniform mat4 modellMatrix;
uniform mat4 viewProjMatrix;
uniform mat4 rayDirMatrix;

out vec4 rayDir;

void main(){
	rayDir = vertexPosition * rayDirMatrix;
	gl_Position = vec4(vertexPosition.xy, 0.0f, 1.0f);
}