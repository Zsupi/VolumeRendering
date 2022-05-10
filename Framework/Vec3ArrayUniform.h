#pragma once
#include "Uniform.h"

class Vec3ArrayUniform : public Uniform {
private:
	std::vector<std::shared_ptr<glm::vec3>> value;
	

public:

	Vec3ArrayUniform(std::vector<std::shared_ptr<glm::vec3>> value, std::string name = "")
		: Uniform(name), value(value) {
	}

	Uniform& setValue(const std::any value) override {
		if (value.type() != typeid(this->value))
			this->value = std::any_cast<std::vector<std::shared_ptr<glm::vec3>>>(value);
		else
			std::cout << "{Error][Uniform] name: " << getName() << " in Vec3ArrayUniform::setValue" << std::endl;
		
		return *this;
	}

	Uniform& commit(Program& program) override {
		program.setUniform(value, getName());
		return *this;
	}

	~Vec3ArrayUniform() {}
};