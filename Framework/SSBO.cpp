#include "SSBO.h"



SSBO::SSBO()
{
	glGenBuffers(1, &ID);
}

void SSBO::Bind()
{
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, ID);
}

void SSBO::Unbind()
{
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

void SSBO::LoadData(std::vector<glm::vec4> data, GLsizeiptr size)
{
	Bind();
	glBufferData(GL_SHADER_STORAGE_BUFFER, size, NULL, GL_DYNAMIC_DRAW);
	glm::vec4* bufferData = (glm::vec4*)glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);

	for (int i = 0; i < size / sizeof(glm::vec4); i++) {
		bufferData[i] = data[i]; // itt még bajos is lehet az indexelés, majd lessem meg
	}

	glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
}

void SSBO::Delete()
{
	glDeleteBuffers(1, &ID);
}
