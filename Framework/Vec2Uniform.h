#pragma once
#include "Uniform.h"

class Vec2Uniform : public Uniform {
private:
	glm::vec2 value;
public:
	Vec2Uniform(const glm::vec2& value = glm::vec2(), std::string name = "") :Uniform(name) {
		this->value = value;
	}
	Uniform& setValue(const std::any value) override {
		if (value.type() != typeid(this->value))
			this->value = std::any_cast<glm::vec2>(value);
		else {
			std::cout << "{Error][Uniform] name: " << getName() << " in Vec2Uniform::setValue" << std::endl;
		}
		return *this;
	}
	Uniform& commit(Program& program) override {
		program.setUniform(value, getName());
		return *this;
	}
};