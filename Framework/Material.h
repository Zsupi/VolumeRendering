#pragma once
#include <memory>
#include "Texture.h"
#include "Program.h"
#include "Uniform.h"

struct Illumination {
	float ambient;
	float diffuse;
	float specular;
	float shininess;
};


class Material {
	std::shared_ptr<Program> program;

	std::unordered_map<std::string, std::shared_ptr<Texture>> textures;
	std::unordered_map<std::string, std::shared_ptr<Uniform>> uniforms;


public:
	Material(std::shared_ptr<Program> program);
	Material(const Material& material);

	Material& addTexture(const std::shared_ptr<Texture> texture, const std::string name);
	Material& addUniform(const std::shared_ptr<Uniform> uniform);
	Material& setIllumination(Illumination illumination);
	Material& setSolidColor(glm::vec3 color);

	Material& setModelMatrix(glm::mat4 modelMatrix, std::string name = "");
	Material& setViewProjMatrix(glm::mat4 viewProjMatrix, std::string name = "");
	Material& setRayDirMatrix(glm::mat4 rayDirMatrix, std::string name = "");

	void bindProgram() const;
	void unbindProgram() const;

	std::shared_ptr<Uniform> operator[](const std::string name);
	Material& operator=(const Material& material);

	void draw();
	

};

// todo: name a value elott legyen => az osszes uniformban is meg kene csinalni