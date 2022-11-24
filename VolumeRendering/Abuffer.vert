#version 430

layout(location = 0) in uint metaballIndex;
layout(std430, binding = 1) buffer positionBuffer {
    vec4 position[];
};

out uint metaballId;
out vec4 pos;


void main () {
    metaballId = gl_VertexID;
    pos = position[2];
    gl_Position = position[gl_VertexID];
}
