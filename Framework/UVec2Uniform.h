#pragma once
#include "Uniform.h"

class UVec2Uniform : public Uniform {
private:
	glm::uvec2 value;
public:
	UVec2Uniform(const glm::uvec2& value = glm::uvec2(), std::string name = "") :Uniform(name) {
		this->value = value;
	}
	Uniform& setValue(const std::any value) override {
		if (value.type() != typeid(this->value))
			this->value = std::any_cast<glm::uvec2>(value);
		else {
			std::cout << "{Error][Uniform] name: " << getName() << " in UVec2Uniform::setValue" << std::endl;
		}
		return *this;
	}
	Uniform& commit(Program& program) override {
		program.setUniform(value, getName());
		return *this;
	}
};