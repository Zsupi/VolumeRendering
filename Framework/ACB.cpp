#include "ACB.h"

ACB::ACB() {
	glGenBuffers(1, &ID);
}

void ACB::Bind() {
	glBindBuffer(GL_ATOMIC_COUNTER_BUFFER, ID);
}

void ACB::Bind(int index) {
	glBindBufferBase(GL_ATOMIC_COUNTER_BUFFER, index, ID);
}

void ACB::Unbind() {
	glBindBuffer(GL_ATOMIC_COUNTER_BUFFER, 0);
}

void ACB::Create() {
	Bind();
	glBufferData(GL_ATOMIC_COUNTER_BUFFER, sizeof(GLuint), NULL, GL_DYNAMIC_DRAW);
	Unbind();
}

void ACB::Reset(int index) {
	Bind();
	GLuint* userCounters = (GLuint*)glMapBufferRange(GL_ATOMIC_COUNTER_BUFFER,
		0,
		sizeof(GLuint),
		GL_MAP_WRITE_BIT 
		| GL_MAP_INVALIDATE_BUFFER_BIT 
		| GL_MAP_UNSYNCHRONIZED_BIT
	);
	memset(userCounters, 0, sizeof(GLuint));
	glUnmapBuffer(GL_ATOMIC_COUNTER_BUFFER);
}

void ACB::Delete() {
	glDeleteBuffers(1, &ID);
}
