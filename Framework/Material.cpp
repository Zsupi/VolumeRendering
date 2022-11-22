#include <iostream>
#include "Material.h"
#include "FloatUniform.h"
#include "Vec3Uniform.h"

Material::Material(std::shared_ptr<Program> program) : program(program) {

}

Material::Material(const Material& material) : program(material.program) {
	textures = material.textures;
	uniforms = material.uniforms;
	//illumination = material.illumination;
}


Material& Material::addTexture(const std::shared_ptr<Texture> texture, const std::string name) {
	textures[name] = texture;
	return *this;
}

Material& Material::addUniform(const std::shared_ptr<Uniform> uniform) {
	uniforms[uniform->getName()] = uniform;
	return *this;
}

Material& Material::setIllumination(Illumination illumination) {
	addUniform(std::make_shared<FloatUniform>(illumination.ambient, "Illumination.ambient"));
	addUniform(std::make_shared<FloatUniform>(illumination.diffuse, "Illumination.diffuse"));
	addUniform(std::make_shared<FloatUniform>(illumination.specular, "Illumination.specular"));
	addUniform(std::make_shared<FloatUniform>(illumination.shininess, "Illumination.shininess"));
	return *this;
}

Material& Material::setSolidColor(glm::vec3 color) {
	addUniform(std::make_shared<Vec3Uniform>(color, "Illumination.solidColor"));
	return *this;
}

Material& Material::setModelMatrix(glm::mat4 modelMatrix, std::string name) {
	program->setUniform(modelMatrix, name.empty() ? "modelMatrix" : name);
	return *this;
}

Material& Material::setViewProjMatrix(glm::mat4 viewProjMatrix, std::string name) {
	program->setUniform(viewProjMatrix, name.empty() ? "viewProjMatrix" : name);
	return *this;
}

Material& Material::setRayDirMatrix(glm::mat4 rayDirMatrix, std::string name) {
	program->setUniform(rayDirMatrix, name.empty() ? "rayDirMatrix" : name);
	return *this;
}

void Material::bindProgram() const{
	program->bind();
}

void Material::unbindProgram() const{
	program->unbind();
}

std::shared_ptr<Uniform> Material::operator[](const std::string name) {
	if (uniforms.find(name) != uniforms.end())
		return uniforms[name];

	else {
		std::cout << "[Error][Material] " << name << " uniform can be found " << std::endl;
		return nullptr;
	}
	
}

Material& Material::operator=(const Material& material) {
	if (&material == this) {
		return *this;
	}
	program = material.program;
	textures = material.textures;
	uniforms = material.uniforms;
	//illumination = material.illumination;
	return *this;
}

void Material::draw() {
	for (auto i : uniforms) {
		i.second->commit(*program.get());
	}
	int slot = 0;
	for (auto i : textures) {
		i.second->bind(slot);
		program->setUniform(slot, i.first);
	}
}
