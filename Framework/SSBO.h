#pragma once
#include <GL/glew.h>
#include <vector>
#include <glm.hpp>
#include <memory.h>

class SSBO
{
public:
	GLuint ID;
	
	SSBO();

	void Bind();
	void Bind(int index);
	void Unbind();
	void LoadData(std::vector<glm::vec4> data, GLsizeiptr size);
	void LoadZeros(GLsizeiptr size);
	void Delete();
};

