#include "Textured3DGeometry.h"
#include "EBO.h"

Textured3DGeometry::Textured3DGeometry(const Textured3DGeometry& geometry) : Geometry(geometry) 
{}

Textured3DGeometry::Textured3DGeometry(std::vector<glm::vec4> vertices, std::vector<glm::vec3> normals, std::vector<glm::vec3> textureCoord, std::vector<int> indices) 
: Geometry(vertices, normals, indices), texCoords(textureCoord) {

	vao.Bind();

	VBO verticesVbo(vertexData);
	VBO texCoordVbo(texCoords);

	EBO ebo(indices);
	
	vao.LinkAttrib(verticesVbo, 0, 4, GL_FLOAT, sizeof(Vertex), NULL);
	vao.LinkAttrib(verticesVbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(4 * sizeof(float)));
	vao.LinkAttrib(texCoordVbo, 2, 3, GL_FLOAT, 0, NULL);

	vao.Unbind();
	verticesVbo.Unbind();
	texCoordVbo.Unbind();
	ebo.Unbind();
}

Textured3DGeometry::Textured3DGeometry(std::vector<Vertex> vertices, std::vector<glm::vec3> textureCoord, std::vector<int> indices)
: Geometry(vertices, indices), texCoords(textureCoord) {

	vao.Bind();

	VBO verticesVbo(vertexData);
	VBO texCoordVbo(texCoords);

	EBO ebo(indices);

	vao.LinkAttrib(verticesVbo, 0, 4, GL_FLOAT, sizeof(Vertex), NULL);
	vao.LinkAttrib(verticesVbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(4 * sizeof(float)));
	vao.LinkAttrib(texCoordVbo, 2, 3, GL_FLOAT, 0, NULL);

	vao.Unbind();
	verticesVbo.Unbind();
	texCoordVbo.Unbind();
	ebo.Unbind();
}

Textured3DGeometry& Textured3DGeometry::operator=(const Textured3DGeometry& geometry) {
	if (this == &geometry)
		return *this;

	Geometry::operator=(geometry);

	return *this;
}

void Textured3DGeometry::draw() {
	vao.Bind();
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	vao.Unbind();
}
