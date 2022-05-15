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

/*
uvec3 dimension = uvec3(3, 3, 3);
	for (int i = 0; i < dimension.x; i++){
		for (int j = 0; j < dimension.y; j++){
			for (int k = 0; k< dimension.z; k++){

				metaballs[i*dimension.y*dimension.z + j * dimension.z + k].radius = 0.5f;//(1 / dimension.x);
				metaballs[i*dimension.y*dimension.z + j * dimension.z + k].center = vec3(-i, -j, -k) / dimension;

			}
		}
	}
*/