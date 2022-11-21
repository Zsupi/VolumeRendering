#pragma once
#include <GL/glew.h>
#include <vector>
#include <glm.hpp>

class SSBO
{
public:
	GLuint ID;
	
	SSBO();

	void Bind();
	void Unbind();
	void LoadData(std::vector<glm::vec4> data, GLsizeiptr size);
	void Delete();
};

