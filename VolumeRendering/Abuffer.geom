#version 430

uniform mat4 modellMatrix;
uniform mat4 viewProjMatrix;

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

out uint ID;
in uint metaballId[];

void main() {
    vec4 center = gl_in[0].gl_Position * viewProjMatrix;
    ID = metaballId[0];

    float metaballSize = 0.2f;

    gl_Position = center;
    gl_Position.x += metaballSize;
    gl_Position.y += metaballSize;
    EmitVertex();

    gl_Position = center;
    gl_Position.x += metaballSize;
    gl_Position.y -= metaballSize;
    EmitVertex();

    gl_Position = center;
    gl_Position.x -= metaballSize;
    gl_Position.y += metaballSize;
    EmitVertex();
    
    gl_Position = center;
    gl_Position.x -= metaballSize;
    gl_Position.y -= metaballSize;
    EmitVertex();

    EndPrimitive();
}