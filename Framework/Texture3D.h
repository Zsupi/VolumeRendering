#pragma once
#include "Texture.h"
class Texture3D : public Texture {
private:
	unsigned int ID;
	int width, height, depth, bpp;
	unsigned char* localBuffer;
public:
	Texture3D(const std::string& filePath, int width = 256, int height = 256, int depth = 256);
	Texture3D(const std::string& filePath, int nPicX, int nPicY);

	void bind(unsigned int slot = 0) const override;
	void unBind() const override;


	~Texture3D();
};

