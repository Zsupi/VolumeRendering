#pragma once
#include "Mesh.h"

struct LightData {
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	glm::vec3 position;

	float linear = 0.09f;
	float quadratic = 0.032f;
};

class Light : public Mesh{

	LightData data;

	static bool visible;

	std::shared_ptr<Uniform> createUniform(const glm::vec3 value, const std::string member, int idx);
	std::shared_ptr<Uniform> createUniform(const float value, const std::string member, int idx);

public:
	Light(LightData lightData);
	
	LightData getData() const;

	Light& setLightUniforms(std::shared_ptr<Material> material, int lightIdx);

	static void setVisibility(bool visibility);

	virtual void draw(std::shared_ptr<Camera> camera) override;
};
//todo type
