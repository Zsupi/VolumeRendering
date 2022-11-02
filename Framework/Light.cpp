#include "Light.h"
#include "Cube.h"
#include "Vec3Uniform.h"
#include "FloatUniform.h"

bool Light::visible = true;

std::shared_ptr<Uniform> Light::createUniform(const glm::vec3 value, const std::string member, int idx) {
	std::string name = std::string("lights[") + std::to_string(idx) + std::string("].");
	
	std::shared_ptr<Vec3Uniform> uniform = std::make_shared<Vec3Uniform>(value, name + member);
	
	return uniform;
}

std::shared_ptr<Uniform> Light::createUniform(const float value, const std::string member, int idx) {
	std::string name = std::string("lights[") + std::to_string(idx) + std::string("].");

	std::shared_ptr<FloatUniform> uniform = std::make_shared<FloatUniform>(value, name + member);

	return uniform;
}

Light::Light(LightData lightData)
	:Mesh(
		std::make_shared<Material>(std::make_shared<Program>("lightVS.glsl", "lightFS.glsl")),
		std::make_shared<Cube>()
	), data(lightData) {
	setPosition(data.position);
	setScale(glm::vec3(0.25f, 0.25f, 0.25f));
	
	std::shared_ptr<Vec3Uniform> ambient = std::make_shared<Vec3Uniform>(data.diffuse, "lightColor");

	material->addUniform(ambient);
}

LightData Light::getData() const {
	return data;
}

Light& Light::setLightUniforms(std::shared_ptr<Material> material, int lightIdx) {
	material->addUniform(createUniform(data.ambient, "ambient", lightIdx));
	material->addUniform(createUniform(data.diffuse, "diffuse", lightIdx));
	material->addUniform(createUniform(data.specular, "specular", lightIdx));
	material->addUniform(createUniform(data.position, "position", lightIdx));

	material->addUniform(createUniform(data.linear, "linear", lightIdx));
	material->addUniform(createUniform(data.quadratic, "quadratic", lightIdx));

	return *this;

}

void Light::setVisibility(bool visibility) {
	visible = visibility;
	
}

void Light::draw(std::shared_ptr<Camera> camera) {
	if (visible) {
		material->bindProgram();

		glm::mat4 modellMatrix;
		glm::mat4 V;
		glm::mat4 P;


		camera->GetMatricies(P, V, modellMatrix);
		glm::mat4 viewProjMatrix = P * V;
		
		modellMatrix = glm::translate(this->getPosition()) * glm::scale(this->getScale());
		material->setModellMatrix(modellMatrix).setViewProjMatrix(viewProjMatrix);


		material->draw();
		geometry->draw();
		
		material->unbindProgram();
	}
}

