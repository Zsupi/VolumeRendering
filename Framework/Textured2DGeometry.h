#pragma once
#include "Geometry.h"

class Textured2DGeometry : public Geometry {
private:
	std::vector<glm::vec2> texCoords;
public:
	Textured2DGeometry(const Textured2DGeometry& geometry);
	Textured2DGeometry(std::vector<glm::vec4> vertieces, std::vector<glm::vec3> normals, std::vector<glm::vec2> textureCoord, std::vector<int> indices);
	Textured2DGeometry(std::vector<Vertex> vertices, std::vector<glm::vec2> textureCoord, std::vector<int> indices);

	Textured2DGeometry& operator=(const Textured2DGeometry& geometry);

	virtual void draw() override;
};

