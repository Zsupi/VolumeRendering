#pragma once
#include "Geometry.h"
class Textured3DGeometry : public Geometry{
private:
	std::vector<glm::vec3> texCoords;
public:
	Textured3DGeometry(const Textured3DGeometry& geometry);
	Textured3DGeometry(std::vector<glm::vec4> vertieces, std::vector<glm::vec3> normals, std::vector<glm::vec3> textureCoord, std::vector<int> indices);
	Textured3DGeometry(std::vector<Vertex> vertices, std::vector<glm::vec3> textureCoord, std::vector<int> indices);

	Textured3DGeometry& operator=(const Textured3DGeometry& geometry);

	virtual void draw() override;
};

