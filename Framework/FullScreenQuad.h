#pragma once
#include "Textured2DGeometry.h"

class FullScreenQuad : public Textured2DGeometry {

public:
	FullScreenQuad();
	const std::vector<glm::vec4> quadVertices();
	const std::vector<glm::vec2> quadTexCoords();
	const std::vector<glm::vec3> quadNormals();
	const std::vector<int> quadIndices();
};

