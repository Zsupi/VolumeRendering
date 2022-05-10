#pragma once
#include <unordered_map>
#include <string>
#include <memory>
#include <glm.hpp>


class Program {
private:
	unsigned int ID;
	std::unordered_map<std::string, int> uniformLocationCache;
	
public:
	Program(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
	~Program();

	void bind() const;
	void unbind() const;

	bool setUniform(float f, const std::string& name);
	bool setUniform(int i, const std::string& name);
	bool setUniform(const glm::vec2& v, const std::string& name);
	bool setUniform(const glm::vec3& v, const std::string& name);
	bool setUniform(const glm::vec4& v, const std::string& name);
	bool setUniform(const glm::mat4& mat, const std::string& name);
	bool setUniform(const std::vector<std::shared_ptr<glm::vec3>> v, const std::string& name);
	
	//Shader& addShader(const std::string geometryShaderPath);
	//Shader& addShader(const std::string hullShaderPath);
	//Shader& addShader(const std::string domainShaderPath);
	
	

private:
	unsigned int compileShader(unsigned int type, const std::string& source);
	unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader);
	int getUniformLocation(const std::string& name);

};

//todo: ProgramCreateFactory