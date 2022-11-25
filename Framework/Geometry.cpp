#include "Geometry.h"

Geometry::Geometry(std::vector<glm::vec4> vertices, std::vector<glm::vec3> normals, std::vector<int> indices) : indices(indices) {
	if (vertices.size() != normals.size()) {
		std::cout << "[Error][Geometry] Vertices, Normals size are not equal" << std::endl;
	}
	for (int i = 0; i < vertices.size(); i++) {
		Vertex vertex;
		vertex.vertex = vertices[i];
		vertex.normal = normals[i];
		vertexData.push_back(vertex);
	}
}

Geometry::Geometry(std::vector<Vertex> vertices, std::vector<int> indices) : indices(indices), vertexData(vertices){
}

Geometry& Geometry::operator=(const Geometry& geometry) {
	if (this == &geometry)
		return *this;
	
	vertexData = geometry.vertexData;
	indices = geometry.indices;
	vao = geometry.vao;

	return *this;
}

Geometry::Geometry(const Geometry& geometry)
	: vao(geometry.vao), vertexData(geometry.vertexData) {
}

Geometry::Geometry() {
}
