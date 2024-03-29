#include "Cube.h"

Cube::Cube():Textured2DGeometry(cubeVertices(), cubeNormals(), cubeTexCoords(), cubeIndices()) {
}

const std::vector<glm::vec4> Cube::cubeVertices() {
    const std::vector<glm::vec4> vertices = {
        glm::vec4(1, 1, -1, 1), glm::vec4(-1, 1, -1, 1), glm::vec4(-1, 1, 1, 1), glm::vec4(1, 1, 1, 1),         // top
        glm::vec4(1, -1, 1, 1), glm::vec4(-1, -1, 1, 1), glm::vec4(-1, -1, -1, 1), glm::vec4(1, -1, -1, 1),     // bottom
        glm::vec4(1, 1, 1, 1), glm::vec4(-1, 1, 1, 1), glm::vec4(-1, -1, 1, 1), glm::vec4(1, -1, 1, 1),         // front face
        glm::vec4(1, -1, -1, 1), glm::vec4(-1, -1, -1, 1), glm::vec4(-1, 1, -1, 1), glm::vec4(1, 1, -1, 1),     // back face
        glm::vec4(-1, 1, 1, 1), glm::vec4(-1, 1, -1, 1), glm::vec4(-1, -1, -1, 1), glm::vec4(-1, -1, 1, 1),     // left
        glm::vec4(1, 1, -1, 1), glm::vec4(1, 1, 1, 1), glm::vec4(1, -1, 1, 1), glm::vec4(1, -1, -1, 1)          // right
    };

    return vertices;
}

const std::vector<glm::vec2> Cube::cubeTexCoords() {
    const std::vector<glm::vec2> texCoods = {
        glm::vec2(0, 0), glm::vec2(1, 0), glm::vec2(1, 1), glm::vec2(0, 1),
        glm::vec2(0, 0), glm::vec2(1, 0), glm::vec2(1, 1), glm::vec2(0, 1),
        glm::vec2(0, 0), glm::vec2(1, 0), glm::vec2(1, 1), glm::vec2(0, 1),
        glm::vec2(0, 0), glm::vec2(1, 0), glm::vec2(1, 1), glm::vec2(0, 1),
        glm::vec2(0, 0), glm::vec2(1, 0), glm::vec2(1, 1), glm::vec2(0, 1),
        glm::vec2(0, 0), glm::vec2(1, 0), glm::vec2(1, 1), glm::vec2(0, 1)
};

    return texCoods;
}

const std::vector<glm::vec3> Cube::cubeNormals() {
    const std::vector<glm::vec3> normals = {
        glm::vec3(0, 1, 0), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0),
        glm::vec3(0, -1, 0), glm::vec3(0, -1, 0), glm::vec3(0, -1, 0), glm::vec3(0, -1, 0),
        glm::vec3(0, 0, 1), glm::vec3(0, 0, 1), glm::vec3(0, 0, 1), glm::vec3(0, 0, 1),
        glm::vec3(0, 0, -1), glm::vec3(0, 0, -1), glm::vec3(0, 0, -1), glm::vec3(0, 0, -1),
        glm::vec3(-1, 0, 0), glm::vec3(-1, 0, 0), glm::vec3(-1, 0, 0), glm::vec3(-1, 0, 0),
        glm::vec3(1, 0, 0), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0)
    };

    return normals;
}

const std::vector<int> Cube::cubeIndices() {
    const std::vector<int> indices = {
         0,1,2,         0,2,3,
         8,9,10,        10,11,8,
         4,5,6,         6,7,4,
         12,13,14,      14,15,12,
         16,17,18,      18,19,16,
         20,21,22,      22,23,20
    };

    return indices;
}