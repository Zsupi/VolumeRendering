#pragma once
#include "Uniform.h"

class FloatUniform : public Uniform {
private:
	float value;
public:
	FloatUniform(const float value = 0.0f, std::string name = "") : Uniform(name) {
		this->value = value;
	}
	Uniform& setValue(const std::any value) override {
		if (value.type() != typeid(this->value))
			this->value = std::any_cast<float>(value);
		else {
			std::cout << "{Error][Uniform] name: " << getName() << " in FloatUniform::setValue" << std::endl;
		}
		return *this;
	}
	Uniform& commit(Program& program) override {
		program.setUniform(value, getName());
		return *this;
	}

};