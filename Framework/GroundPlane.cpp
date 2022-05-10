#include "GroundPlane.h"

GroundPlane::GroundPlane(): Textured2DGeometry(groundVertexData(), groundTexCoords(), groundIndices()) {
}

const std::vector<glm::vec4> GroundPlane::groundVertices() {
    const std::vector<glm::vec4> vertices = {
        glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
        glm::vec4(1.0f, 0.0f, 0.0f, 0.0f),
        glm::vec4(0.0f, 0.0f, 1.0f, 0.0f),
        glm::vec4(-1.0f, 0.0f, 0.0f, 0.0f),
        glm::vec4(0.0f, 0.0f, -1.0f, 0.0f)
    };
    return vertices;
}

const std::vector<glm::vec2> GroundPlane::groundTexCoords() {
    return  std::vector<glm::vec2>();
}

const glm::vec3 GroundPlane::groundNormal() {
    return glm::vec3(0.0f, 1.0f, 0.0f);
}

const std::vector<int> GroundPlane::groundIndices() {
    const std::vector<int> indices{
        0,1,2,
        0,2,3,
        0,3,4,
        0,4,1
    };
    return indices;
}

const std::vector<Vertex> GroundPlane::groundVertexData() {
    std::vector<Vertex> vertexData;

    std::vector<glm::vec4> vertices = groundVertices();
    glm::vec3 normal = groundNormal();
    for (int i = 0; i < vertices.size(); i++) {
        Vertex vertex;
        vertex.vertex = vertices[i];
        vertex.normal = normal;
        vertexData.push_back(vertex);
    }

    return vertexData;
}
