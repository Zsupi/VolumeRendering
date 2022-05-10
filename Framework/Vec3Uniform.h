#pragma once
#include "Uniform.h"

class Vec3Uniform : public Uniform {
private:
	glm::vec3 value;
public:
	Vec3Uniform(const glm::vec3& value = glm::vec3(), std::string name = ""):Uniform(name) {
		this->value = value;
	}
	Uniform& setValue(const std::any value) override {
		if (value.type() != typeid(this->value))
			this->value = std::any_cast<glm::vec3>(value);
		else {
			std::cout << "{Error][Uniform] name: " << getName() << " in Vec3Uniform::setValue" << std::endl;
		}
		return *this;
	}
	Uniform& commit(Program& program) override {
		program.setUniform(value, getName());
		return *this;
	}

	~Vec3Uniform() {}
};