#pragma once

#include <memory>
#include <vector>
#include <glm.hpp>

struct VolumeVertex {
	std::shared_ptr<glm::vec3> position;
	std::shared_ptr<glm::vec3> texCoord;
};

class VolumeGeometryInterface {

public:

	/// <summary>
	/// Returns the VolumeVertex in the given position
	/// </summary>
	/// <param name="i"> index of the x dimension </param>
	/// <param name="j"> index of the y dimension </param>
	/// <param name="k"> index of the z dimension </param>
	/// <returns> VolumeVertex </returns>
	virtual VolumeVertex& at(size_t i, size_t j, size_t k) = 0;

	/// <summary>
	/// Returns the array of VolumeVertices's positions
	/// </summary>
	/// <returns> array of glm::vec3 shared_ptr </returns>
	virtual std::vector<std::shared_ptr<glm::vec3>> getPositions() const = 0;

	/// <summary>
	/// Returns the array of VolumeVertices's texCoords
	/// </summary>
	/// <returns> array of glm::vec3 shared_ptr </returns>
	virtual std::vector<std::shared_ptr<glm::vec3>> getTexCoords() const = 0;
	
	/// <summary>
	/// Returns the dimension of the volume
	/// </summary>
	/// <returns> 3 unsingned integers </returns>
	virtual glm::uvec3 getDimension() const = 0;

};