#include "VolumeGeometry.h"

VolumeGeometry::VolumeGeometry(size_t x, size_t y, size_t z, std::vector<VolumeVertex> vertices) 
	: dimension(x, y, z), vertices(vertices) {
}

VolumeGeometry::VolumeGeometry(size_t x, size_t y, size_t z, std::vector<std::shared_ptr<glm::vec3>> positions)
	: dimension(x, y, z) {

	glm::vec3 texCoord = glm::vec3();

	for (int i = 0; i < positions.size(); i++) {
		VolumeVertex vertex;

		texCoord.x += 1.0f / x;

		if (texCoord.x > 1.0f) {
			texCoord.x = 0.0f;
			texCoord.y += 1.0f / y;
		}

		if (texCoord.y > 1.0f) {
			texCoord.y = 0.0f;
			texCoord.z += 1.0f / z;
		}

		vertex.position = positions[i];
		vertex.texCoord = std::make_shared<glm::vec3>(texCoord);
		vertices.push_back(vertex);
	}
}

VolumeVertex& VolumeGeometry::at(size_t i, size_t j, size_t k) {
	return vertices[i * dimension.y * dimension.z + j * dimension.z + k];
}

std::vector<std::shared_ptr<glm::vec3>> VolumeGeometry::getPositions() const {
	std::vector<std::shared_ptr<glm::vec3>> positions;

	for (auto i : vertices)
		positions.push_back(i.position);

	return positions;
}

std::vector<std::shared_ptr<glm::vec3>> VolumeGeometry::getTexCoords() const {
	std::vector<std::shared_ptr<glm::vec3>> texCoords;

	for (auto i : vertices)
		texCoords.push_back(i.texCoord);

	return texCoords;
}


glm::uvec3 VolumeGeometry::getDimension() const {
	return dimension;
}
