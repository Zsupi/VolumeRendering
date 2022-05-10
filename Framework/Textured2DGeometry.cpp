#include "Textured2DGeometry.h"
#include "EBO.h"

Textured2DGeometry::Textured2DGeometry(const Textured2DGeometry& geometry) : Geometry(geometry)
{}

Textured2DGeometry::Textured2DGeometry(std::vector<glm::vec4> vertices, std::vector<glm::vec3> normals, std::vector<glm::vec2> textureCoord, std::vector<int> indices)
: Geometry(vertices, normals, indices), texCoords(textureCoord) {
	

	vao.Bind();

	VBO verticesVbo(vertexData);
	VBO texCoordVbo(texCoords);

	EBO ebo(indices);
	//todo
	vao.LinkAttrib(verticesVbo, 0, 4, GL_FLOAT, sizeof(Vertex), NULL);
	vao.LinkAttrib(verticesVbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(4 * sizeof(float)));
	vao.LinkAttrib(texCoordVbo, 2, 2, GL_FLOAT, 0, NULL);

	vao.Unbind();
	verticesVbo.Unbind();
	texCoordVbo.Unbind();
	ebo.Unbind();
}

Textured2DGeometry::Textured2DGeometry(std::vector<Vertex> vertices, std::vector<glm::vec2> textureCoord, std::vector<int> indices)
: Geometry(vertices, indices), texCoords(textureCoord) {

	vao.Bind();

	VBO verticesVbo(vertices);
	VBO texCoordVbo(texCoords);

	EBO ebo(indices);

	vao.LinkAttrib(verticesVbo, 0, 4, GL_FLOAT, sizeof(Vertex), NULL);
	vao.LinkAttrib(verticesVbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(4 * sizeof(float)));
	vao.LinkAttrib(texCoordVbo, 2, 2, GL_FLOAT, 0, NULL);

	vao.Unbind();
	verticesVbo.Unbind();
	texCoordVbo.Unbind();
	ebo.Unbind();
}

Textured2DGeometry& Textured2DGeometry::operator=(const Textured2DGeometry& geometry) {
	if (this == &geometry)
		return *this;

	Geometry::operator=(geometry);
	
	return *this;
}

void Textured2DGeometry::draw() {
	vao.Bind();
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	vao.Unbind();
}