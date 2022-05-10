#version 330

precision highp float;


uniform vec3 cameraPos;

uniform sampler3D textureColor;

in struct{
	vec3 normal;
	vec3 position;
    vec3 texCoord;
}VSO;

out vec4 fragmentColor;

void main(){
    vec3 norm = normalize(VSO.normal);
    vec3 viewDir = normalize(cameraPos - VSO.position);

    vec4 color = texture(textureColor, VSO.texCoord);
    if (color.x < 0.07)
        color.w = 0;
    fragmentColor = color;
}