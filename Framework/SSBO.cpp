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

//Different functions for different kind of buffers(vec4, vec3 etc.)

void SSBO::LoadData(std::vector<glm::vec4> data, GLsizeiptr size)
{
	Bind();
	//glBufferData(GL_SHADER_STORAGE_BUFFER, size, data.data(), GL_DYNAMIC_DRAW);
	glBufferData(GL_SHADER_STORAGE_BUFFER, size, NULL, GL_DYNAMIC_DRAW);
	glm::vec4* bufferData = (glm::vec4*)glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_READ_WRITE);
	for (int i = 0; i < size / sizeof(glm::vec4); i++) {
		bufferData[i] = data[i];
	}
	glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
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

void SSBO::Delete()
{
	glDeleteBuffers(1, &ID);
}
