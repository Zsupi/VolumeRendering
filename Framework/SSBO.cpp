#include "SSBO.h"

SSBO::SSBO()
{
	glGenBuffers(1, &ID);
}

void SSBO::Bind()
{
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, ID);
}

void SSBO::Bind(int index)
{
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, index, ID);
}

void SSBO::Unbind()
{
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

/*
	In case you using std430 or std140:

	Among the most important is the fact that arrays of types are not necessarily tightly packed. 
	An array of float​s in such a block will not be the equivalent to an array of floats​ in C/C++. 
	The array stride (the bytes between array elements) is always rounded up to the size of a vec4​ (ie: 16-bytes).
	So arrays will only match their C/C++ definitions if the type is a multiple of 16 bytes.

	OpenGL specification (OpenGL 4.5, Section 7.6.2.2, page 137)
*/

void SSBO::LoadData(std::vector<glm::vec4> data, GLsizeiptr size)
{
	Bind();
	glBufferData(GL_SHADER_STORAGE_BUFFER, size, data.data(), GL_DYNAMIC_DRAW);
}

void SSBO::LoadZeros(GLsizeiptr size)
{
	Bind();
	glBufferData(GL_SHADER_STORAGE_BUFFER, size, NULL, GL_DYNAMIC_DRAW);
	glm::vec4* bufferData = (glm::vec4*)glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_READ_WRITE);
	for (int i = 0; i < size / sizeof(glm::vec4); i++) {
		bufferData[i] = glm::vec4(0);
	}
	glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
}

void SSBO::LoadData(std::vector<SSBO::uint_element> data, GLsizeiptr size) {
	Bind();
	glBufferData(GL_SHADER_STORAGE_BUFFER, size, data.data(), GL_DYNAMIC_DRAW);
}

void SSBO::LoadData(std::vector<SSBO::uvec2_element> data, GLsizeiptr size) {
	Bind();
	glBufferData(GL_SHADER_STORAGE_BUFFER, size, data.data(), GL_DYNAMIC_DRAW);
}

void SSBO::Delete()
{
	glDeleteBuffers(1, &ID);
}
