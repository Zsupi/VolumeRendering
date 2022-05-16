#pragma once
#include "VolumeGeometryInterface.h"


/// <summary>
/// 3D holder of the vertices of the volumegeometry with 1 dimension std::vector array
/// </summary>
class VolumeGeometry : public VolumeGeometryInterface{
	std::vector<VolumeVertex> vertices;
	glm::uvec3 dimension;

public:
	VolumeGeometry(size_t x, size_t y, size_t z, std::vector<VolumeVertex> vertices);

	VolumeGeometry(size_t x, size_t y, size_t z, std::vector<std::shared_ptr<glm::vec3>> positions);

	VolumeVertex& at(size_t i, size_t j, size_t k) override;

	std::vector<std::shared_ptr<glm::vec3>> getPositions() const override;

	std::vector<std::shared_ptr<glm::vec3>> getTexCoords() const override;

	glm::uvec3 getDimension() const override;

};