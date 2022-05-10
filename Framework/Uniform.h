#pragma once
#include <any>
#include <iostream>
#include "Program.h"
class Uniform{
private:
	std::string name;

	Uniform() {}

protected:
	Uniform(const std::string& name) {
		this->name = name;
	}

public:

	virtual Uniform& setValue(const std::any value) = 0;
	virtual Uniform& commit(Program& program) = 0;

	std::string getName() const {
		return name;
	}

	virtual ~Uniform() {};
};

