#pragma once
#include <Mesh.h>
#include "VolumeGeometryInterface.h"
class VolumeMesh : public Mesh{

	std::shared_ptr<VolumeGeometryInterface> volumeGeometry;

public:

	VolumeMesh(std::shared_ptr<VolumeGeometryInterface> volumeGeometry, std::shared_ptr<Material> material, std::shared_ptr<Geometry> geometry);

	void draw(std::shared_ptr<Camera> camera) override;
};

