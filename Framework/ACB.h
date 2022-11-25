#pragma once
#include <GL/glew.h>
#include <vector>
#include <glm.hpp>

/*
* Atomic counter buffer
* For more information = https://www.khronos.org/opengl/wiki/Atomic_Counter
*/

class ACB {
public:
	GLuint ID;

	ACB();

	void Bind();
	void Bind(int index);
	void Unbind();
	void Create();
	void Reset(int index);
	void Delete();
};
