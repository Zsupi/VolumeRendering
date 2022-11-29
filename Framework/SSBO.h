#pragma once
#include <GL/glew.h>
#include <vector>
#include <glm.hpp>
#include <memory.h>


class SSBO
{
	

public:

#pragma region Custom_Buffer_Elements
	/*
		Struct for custom buffer elements.

		Padding is needed to scale the buffer's element up to 16 byte (vec4 in glsl).
		Otherwise the std430 or std140 type buffers won't work properly.
	*/
	struct uint_element {
		unsigned int pixel = 0;
	private:
		float __padding[3] = { 0.0f, 0.0f, 0.0f };
	};

	struct uvec2_element {
		glm::uvec2 element = glm::vec2(0);
	private:
		float __padding[2] = { 0.0f, 0.0f };
	};
#pragma endregion


	GLuint ID;
	
	SSBO();

	void Bind();
	void Bind(int index);
	void Unbind();
	void LoadData(std::vector<glm::vec4> data, GLsizeiptr size);
	void LoadData(std::vector<uint_element> data, GLsizeiptr size);
	void LoadData(std::vector<uvec2_element> data, GLsizeiptr size);
	void LoadZeros(GLsizeiptr size);
	void Delete();
};

