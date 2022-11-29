#include "Program.h"
#include "Common.h"
#include <GL/glew.h>
#include <gtc/type_ptr.hpp>


Program::Program()
	: ID(0) {
	ID = glCreateProgram();
}

Program::Program(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
	: ID(0) {
	ID = glCreateProgram();

	unsigned int vertexId = CreateShader(GL_VERTEX_SHADER, vertexShaderPath);
	unsigned int fragmentId = CreateShader(GL_FRAGMENT_SHADER, fragmentShaderPath);

	Program::attachShader(vertexId);
	Program::attachShader(fragmentId);

	Program::linkProgram();

}

Program::~Program() {
	glDeleteProgram(ID);
}

void Program::bind() const {
	glUseProgram(ID);
}

void Program::unbind() const {
	glUseProgram(0);
}

bool Program::setUniform(float f, const std::string& name) {
	int location = getUniformLocation(name);
	if (location >= 0) glUniform1f(location, f);
	return location >= 0;
}

bool Program::setUniform(const glm::vec2& v, const std::string& name) {
	int location = getUniformLocation(name);
	if (location >= 0) glUniform2fv(location, 1, &v.x);
	return location >= 0;
}

bool Program::setUniform(const glm::uvec2& v, const std::string& name) {
	int location = getUniformLocation(name);
	if (location >= 0) glUniform2uiv(location, 1, &v.x);
	return location >= 0;
}

bool Program::setUniform(const glm::vec3& v, const std::string& name) {
	int location = getUniformLocation(name);
	if (location >= 0) glUniform3fv(location, 1, &v.x);
	return location >= 0;
}

bool Program::setUniform(const glm::vec4& v, const std::string& name) {
	int location = getUniformLocation(name);
	if (location >= 0) glUniform4fv(location, 1, &v.x);
	return location >= 0;
}

bool Program::setUniform(const glm::mat4& mat, const std::string& name) {
	int location = getUniformLocation(name);
	if (location >= 0) 
		glUniformMatrix4fv(location, 1, GL_TRUE, glm::value_ptr(mat));
	return location >= 0;
}

bool Program::setUniform(const std::vector<std::shared_ptr<glm::vec3>> v, const std::string& name) {
	int location = getUniformLocation(name);
	if (location >= 0)
		glUniform3fv(location, v.size(), &v[0]->x);
	return location >= 0;
}

bool Program::setUniform(int i, const std::string& name) {
	int location = getUniformLocation(name);
	if (location >= 0)
		glUniform1i(location, i);
	return location >= 0;
}

Program& Program::attachShader(const unsigned int shaderID)
{
	shaders.push_back(shaderID);
	return *this;
}

Program& Program::linkProgram() {

	for (unsigned int shaderID : shaders) {
		glAttachShader(ID, shaderID);
		glDeleteShader(shaderID);
	}

	shaders.clear();

	glLinkProgram(ID);
	glValidateProgram(ID);
	return *this;
}

int Program::getUniformLocation(const std::string& name){
	if (uniformLocationCache.find(name) != uniformLocationCache.end())
		return uniformLocationCache[name];

	int location = glGetUniformLocation(ID, name.c_str());
	if (location < 0)
		std::cout << "[Error][Program] uniform " << name.c_str() << " cannot be set" << std::endl;
	
	uniformLocationCache[name] = location;

	return location;
}