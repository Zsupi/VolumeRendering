#pragma once
#include "Textured2DGeometry.h"
class GroundPlane : public Textured2DGeometry {
public:
	GroundPlane();

    const std::vector<glm::vec4> groundVertices();
    const std::vector<glm::vec2> groundTexCoords();
    const glm::vec3 groundNormal();
    const std::vector<int> groundIndices();
    const std::vector<Vertex> groundVertexData();
};

