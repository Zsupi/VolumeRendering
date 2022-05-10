#pragma once
#include "Textured2DGeometry.h"

class Cube : public Textured2DGeometry{
    
public:
    Cube();

    const std::vector<glm::vec4> cubeVertices();
    const std::vector<glm::vec2> cubeTexCoords();
    const std::vector<glm::vec3> cubeNormals();
    const std::vector<int> cubeIndices();

};
