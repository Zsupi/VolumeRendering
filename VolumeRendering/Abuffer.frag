# version 430

precision highp float;

struct Screen {
    uint pixel;
    float padding[3];
};

struct LinkedListElement {
    uvec2 element;
    float padding[2];
};

// holds the index of the first element of the linked list
layout(std430, binding = 2) buffer screenBuffer {
    Screen screen[];
};

// element.x stands for the index of the previous element
// element.y stands for the metaballId
layout(std430, binding = 3) buffer linkedListBuffer {
    LinkedListElement element[];
};

// counter for new linked list elements
layout(binding = 0, offset = 0) uniform atomic_uint counter;

uniform uvec2 windowSize = uvec2(600, 600);

flat in uint id;

out vec4 fragmentColor;

void main() {
    uint pixelId = uint(gl_FragCoord.y) * (windowSize.x-1) + uint(gl_FragCoord.x);

    uint pixelCount = atomicCounterIncrement(counter);

    if (pixelCount < element.length()-1) {
        uint previousElement = screen[pixelId].pixel;
        atomicExchange(screen[pixelId].pixel, pixelCount);

        element[pixelCount].element.x = previousElement;
        element[pixelCount].element.y = id;
        
        vec3 color = vec3(id/216.0f, 1.0f, 1.0f);
        fragmentColor = vec4(color, 1.0f);
    }
}