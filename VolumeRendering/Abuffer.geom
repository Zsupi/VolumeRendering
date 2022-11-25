#version 430

uniform mat4 modellMatrix;
uniform mat4 viewProjMatrix;

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

in uint metaballId[];

out Vertex {
    uint metaballId;
    vec4 position;
}vertex;

void main() {
    vec4 center = gl_in[0].gl_Position * viewProjMatrix;

    float metaballSize = 0.2f;

    gl_Position = center;
    gl_Position.x += metaballSize;
    gl_Position.y += metaballSize;
    vertex.metaballId = metaballId[0];
    vertex.position = gl_Position;
    EmitVertex();

    gl_Position = center;
    gl_Position.x += metaballSize;
    gl_Position.y -= metaballSize;
    vertex.metaballId = metaballId[0];
    vertex.position = gl_Position;
    EmitVertex();

    gl_Position = center;
    gl_Position.x -= metaballSize;
    gl_Position.y += metaballSize;
    vertex.metaballId = metaballId[0];
    vertex.position = gl_Position;
    EmitVertex();
    
    gl_Position = center;
    gl_Position.x -= metaballSize;
    gl_Position.y -= metaballSize;
    vertex.metaballId = metaballId[0];
    vertex.position = gl_Position;
    EmitVertex();

    EndPrimitive();
}