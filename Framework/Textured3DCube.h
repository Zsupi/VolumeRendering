#pragma once
#include "Textured3DGeometry.h"
class Textured3DCube : public Textured3DGeometry{
public:
	Textured3DCube();

	const std::vector<glm::vec4> cubeVertices();
	const std::vector<glm::vec3> cubeTexCoords();
	const std::vector<glm::vec3> cubeNormals();
	const std::vector<int> cubeIndices();
};

