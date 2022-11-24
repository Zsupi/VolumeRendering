# version 430

precision highp float;

vec3 color = vec3(0, 1.0f, 1.0f);

out vec4 fragmentColor;

void main() {
    fragmentColor = vec4(color, 1.0f);
}