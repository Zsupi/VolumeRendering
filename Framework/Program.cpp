#include "Program.h"
#include "Common.h"
#include <GL/glew.h>
#include <gtc/type_ptr.hpp>

Program::Program(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
	: ID(0) {

	std::string vertexShader = File::readFile(vertexShaderPath.c_str());
	std::string fragmentShader = File::readFile(fragmentShaderPath.c_str());
	ID = createShader(vertexShader, fragmentShader);

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

unsigned int Program::compileShader(unsigned int type, const std::string& source) {
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);
	//todo: Error handling: https://docs.gl/es3/glShaderSource
	GLint isCompiled = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_FALSE) {
		GLint maxLength = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(id, maxLength, &maxLength, &infoLog[0]);

		for (auto i : infoLog) {
			std::cout << i;
		}
		std::cout << std::endl;
	}


	return id;
}

unsigned int Program::createShader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource) {
	unsigned int program = glCreateProgram();
	unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
	unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

	glAttachShader(program, vs);
	glAttachShader(program, fs);

	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);


	return program;
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