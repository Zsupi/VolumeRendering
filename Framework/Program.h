#pragma once
#include <unordered_map>
#include <string>
#include <memory>
#include <glm.hpp>
#include "Shader.h"

class Program {
private:
	unsigned int ID;
	std::list<unsigned int> shaders;
	std::unordered_map<std::string, int> uniformLocationCache;
	
public:
	Program();
	//for backwards compatibility
	Program(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
	~Program();

	void bind() const;
	void unbind() const;

	Program& attachShader(const unsigned int shaderID);
	Program& linkProgram();

	bool setUniform(float f, const std::string& name);
	bool setUniform(int i, const std::string& name);
	bool setUniform(const glm::vec2& v, const std::string& name);
	bool setUniform(const glm::vec3& v, const std::string& name);
	bool setUniform(const glm::vec4& v, const std::string& name);
	bool setUniform(const glm::mat4& mat, const std::string& name);
	bool setUniform(const std::vector<std::shared_ptr<glm::vec3>> v, const std::string& name);
	
private:
	int getUniformLocation(const std::string& name);

};

//todo: ProgramCreateFactory