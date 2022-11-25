#pragma once
#include <vector>
#include <iostream>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>
#include "VAO.h"

class Geometry {
protected:
	std::vector<Vertex> vertexData;
	std::vector<int> indices;

	VAO vao;
	Geometry(std::vector<glm::vec4> vertieces, std::vector<glm::vec3> normals, std::vector<int> indices);
	Geometry(std::vector<Vertex> vertices, std::vector<int> indices);
	Geometry(const Geometry& geometry);
	Geometry();

public:
	Geometry& operator=(const Geometry& geometry);

	std::vector<Vertex> getVerticiesData() const {
		return this->vertexData;
	}

	virtual void draw() = 0;
};

