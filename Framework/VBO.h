#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <GL/glew.h>
#include <vector>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>

struct Vertex {
	glm::vec4 vertex;
	glm::vec3 normal;
};

class VBO
{
public:
	// Reference ID of the Vertex Buffer Object
	GLuint ID;
	// Constructor that generates a Vertex Buffer Object and links it to vertices
	VBO(std::vector<Vertex> vertices);
	VBO(std::vector<glm::vec2> texCoord);
	VBO(std::vector<glm::vec3> texCoord);
	// Binds the VBO
	void Bind();
	// Unbinds the VBO
	void Unbind();
	// Deletes the VBO
	void Delete();
};

#endif