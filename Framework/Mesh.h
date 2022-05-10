#pragma once
#include "Material.h"
#include "Geometry.h"
#include "Camera.h"

class Mesh {

protected:
	std::shared_ptr<Material> material;
	std::shared_ptr<Geometry> geometry;

private:
	glm::vec3 position;
	float roll;
	glm::vec3 scale;

public:
	
	Mesh(std::shared_ptr<Material> material, std::shared_ptr<Geometry> geometry);
	Mesh(const Mesh& mesh);

	glm::vec3 getPosition() const;
	float getRoll() const;
	glm::vec3 getScale() const;

	Mesh& setPosition(glm::vec3 position);
	Mesh& setRoll(float roll);
	Mesh& setScale(glm::vec3 scale);

	Mesh& translate(glm::vec3& translation);
	Mesh& rotate(float rotation);

	virtual void draw(std::shared_ptr<Camera> camera);

	Mesh& operator=(const Mesh& mesh);

	virtual ~Mesh() {}
};

