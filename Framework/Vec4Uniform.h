#pragma once
#include "Uniform.h"

class Vec4Uniform : public Uniform{
private:
	glm::vec4 value;
public:
	Vec4Uniform(const glm::vec4& value = glm::vec4(), std::string name = "") :Uniform(name) {
		this->value = value;
	}
	Uniform& setValue(const std::any value) {
		if (value.type() != typeid(this->value))
			this->value = std::any_cast<glm::vec4>(value);
		else {
			std::cout << "{Error][Uniform] name: " << getName() << " in Vec4Uniform::setValue" << std::endl;
		}
		return *this;
	}
	Uniform& commit(Program& program) override {
		program.setUniform(value, getName());
		return *this;
	}

};

