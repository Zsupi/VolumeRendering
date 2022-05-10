#pragma once
#include "Texture.h"

class Texture2D final : public Texture{
private:
	unsigned int ID;
	int width, height, bpp;
	unsigned char* localBuffer;
public:
	Texture2D(const std::string& filePath);

	void bind(unsigned int slot = 0) const override;
	void unBind() const override;

	~Texture2D();
};

