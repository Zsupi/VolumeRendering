#pragma once
#include "Uniform.h"

class IntUniform : public Uniform {
private:
	int value;
public:
	IntUniform(const int value = 0, std::string name = "") : Uniform(name) {
		this->value = value;
	}
	Uniform& setValue(const std::any value) override {
		if (value.type() != typeid(this->value))
			this->value = std::any_cast<int>(value);
		else {
			std::cout << "{Error][Uniform] name: " << getName() << " in IntUniform::setValue" << std::endl;
		}
		return *this;
	}
	Uniform& commit(Program& program) override {
		program.setUniform(value, getName());
		return *this;
	}

};