# version 430

precision highp float;

// holds the index of the first element of the linked list
layout(std430, binding = 2) buffer screenBuffer {
    uint screen[];
};

// element.x stands for the index of the previous element
// element.y stands for the metaballId
layout(std430, binding = 3) buffer linkedListBuffer {
    uvec2 element[];
};

// counter for new linked list elements
layout(binding = 0, offset = 0) uniform atomic_uint counter;


uniform uvec2 windowSize;

in Vertex {
    flat uint metaballId;
    vec4 position;
}vertex;

out vec4 fragmentColor;

void main() {
    uint pixelId = uint(vertex.position.y) * windowSize.x + uint(vertex.position.x);
    
    uint pixelCount = atomicCounterIncrement(counter);

    uint previousElement = screen[pixelId];
    //atomicExchange(screen[pixelId], pixelCount);
    
    
    uvec2 newElement;
    newElement.x = previousElement;
    newElement.y = vertex.metaballId;

    //element[pixelCount] = newElement;

    //vec3 color = vec3(0, 1.0f, float(previousElement));
    vec3 color = vec3(0, 1.0f, 1.0f);
    fragmentColor = vec4(color, 1.0f);
}