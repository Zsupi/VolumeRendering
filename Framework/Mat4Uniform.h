#pragma once
#include "Uniform.h"
class Mat4Uniform : public Uniform{
private:
	glm::mat4 value;
public:
	Mat4Uniform(const glm::mat4& value = glm::mat4(), std::string name = ""):Uniform(name){
		this->value = value;
	}
	Uniform& setValue(const std::any value) override {
		if (value.type() != typeid(this->value))
			this->value = std::any_cast<glm::mat4>(value);
		else {
			std::cout << "{Error][Uniform] name: " << getName() << " in Mat4Uniform::setValue" << std::endl;
		}
		return *this;
	}
	Uniform& commit(Program& program) override {
		program.setUniform(value, getName());
		return *this;
	}
};

