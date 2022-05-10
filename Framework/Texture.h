#pragma once
#include <string>

class Texture {
private:
	std::string filePath;

protected:
	std::string getFilePath() const { return filePath; }
	Texture(const std::string& filePath);

public:
	virtual void bind(unsigned int slot = 0) const = 0;
	virtual void unBind() const = 0;
	virtual ~Texture() {};
};