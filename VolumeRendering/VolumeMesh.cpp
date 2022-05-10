#include <Vec3Uniform.h>
#include <Vec3ArrayUniform.h>
#include "VolumeMesh.h"

VolumeMesh::VolumeMesh(std::shared_ptr<VolumeGeometryInterface> volumeGeometry, std::shared_ptr<Material> material, std::shared_ptr<Geometry> geometry)
	: Mesh(material, geometry), volumeGeometry(volumeGeometry) {

	material->addUniform(std::make_shared<Vec3ArrayUniform>(volumeGeometry->getPositions(), "volumeData.position"));
	material->addUniform(std::make_shared<Vec3ArrayUniform>(volumeGeometry->getTexCoords(), "volumeData.texCoords"));
	material->addUniform(std::make_shared<Vec3Uniform>(volumeGeometry->getDimension(), "volumeData.volumeDimension"));	
}

void VolumeMesh::draw(std::shared_ptr<Camera> camera) {
	material->bindProgram();

	glm::mat4 Ray;
	camera->GetRayDir(Ray);
	material->setRayDirMatrix(Ray);
	material->addUniform(std::make_shared<Vec3Uniform>(camera->camera_position, "cameraPos"));

	material->draw();
	geometry->draw();

	material->unbindProgram();
	
}
