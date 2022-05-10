#include "FullScreenQuad.h"

FullScreenQuad::FullScreenQuad():Textured2DGeometry(quadVertices(), quadNormals(), quadTexCoords(), quadIndices()) {
}

const std::vector<glm::vec4> FullScreenQuad::quadVertices() {
    const std::vector<glm::vec4> vertices = {
        glm::vec4(-1, -1, 0, 1),
        glm::vec4(-1, 1, 0, 1),
        glm::vec4(1, -1, 0, 1),
        glm::vec4(1, 1, 0, 1)
    };
    
    return vertices;
}

const std::vector<glm::vec2> FullScreenQuad::quadTexCoords() {
    const std::vector<glm::vec2> texCoords = {
        glm::vec2(0, 1),
        glm::vec2(0, 0),
        glm::vec2(1, 1),
        glm::vec2(1, 0)
    };
    
    return texCoords;
}

const std::vector<glm::vec3> FullScreenQuad::quadNormals() {
    const std::vector<glm::vec3> normals = {
        glm::vec3(0, 0, 1),
        glm::vec3(0, 0, 1),
        glm::vec3(0, 0, 1),
        glm::vec3(0, 0, 1),
    };

    return normals;
}

const std::vector<int> FullScreenQuad::quadIndices() {
    const std::vector<int> indices = {
        0, 1, 2,
        1, 2, 3
    };
    
    return indices;
}
