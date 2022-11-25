#include "Mesh.h"
#include "Vec3Uniform.h"

Mesh::Mesh(std::shared_ptr<Material> material, std::shared_ptr<Geometry> geometry) :material(material), geometry(geometry) {
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	roll = 0.0f;
	scale = glm::vec3(1.0f, 1.0f, 1.0f);
}

Mesh::Mesh(const Mesh& mesh)
	:material(mesh.material), geometry(mesh.geometry), position(mesh.position),
	 roll(mesh.roll), scale(mesh.scale) {
}

glm::vec3 Mesh::getPosition() const {
	return position;
}

float Mesh::getRoll() const {
	return roll;
}

glm::vec3 Mesh::getScale() const {
	return scale;
}

Mesh& Mesh::setPosition(glm::vec3 position) {
	this->position = position;
	return *this;
}

Mesh& Mesh::setRoll(float roll) {
	this->roll = roll;
	return *this;
}

Mesh& Mesh::setScale(glm::vec3 scale) {
	if (scale.x < 0 || scale.y < 0 || scale.z < 0) {
		std::cout << "[Error][Mesh] Scale cannot be minus" << std::endl;
		return *this;
	}

	this->scale = scale;
	return *this;
}

Mesh& Mesh::translate(glm::vec3& translation) {
	position += translation;
	return *this;
}

Mesh& Mesh::rotate(float rotation) {
	roll += rotation;
	return *this;
}

void Mesh::draw(std::shared_ptr<Camera> camera) {
	material->bindProgram();
	
	glm::mat4 modelMatrix;
	glm::mat4 V;
	glm::mat4 P;
	glm::mat4 Ray;

	camera->GetMatricies(P, V, modelMatrix);
	camera->GetRayDir(Ray);
	glm::mat4 viewProjMatrix = P * V;

	modelMatrix =  glm::translate(position) * glm::scale(scale);
	material->setModelMatrix(modelMatrix)
		.setViewProjMatrix(viewProjMatrix)
		.setRayDirMatrix(Ray);
	material->addUniform(std::make_shared<Vec3Uniform>(camera->camera_position, "cameraPos"));

	material->draw();
	geometry->draw();

	material->unbindProgram();
}

Mesh& Mesh::operator=(const Mesh& mesh) {

	if (this == &mesh) {
		return *this;
	}
	material = mesh.material;
	geometry = mesh.geometry;

	position = mesh.position;
	roll = mesh.roll;
	scale = mesh.scale;

	return *this;
}

