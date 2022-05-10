#include "Texture3D.h"
#include <GL/glew.h>
#include "stb_image.h"

Texture3D::Texture3D(const std::string& filePath, int width, int height, int depth): Texture(filePath), 
width(width), height(height), depth(depth), bpp(0) {
	stbi_set_flip_vertically_on_load(1);
	int widthPicture, heightPicture = 0;
	localBuffer = stbi_load(getFilePath().c_str(), &widthPicture, &heightPicture, &bpp, 4);

	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_3D, ID);

	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glTexImage3D(GL_TEXTURE_3D, 0, GL_R8, width, height, depth, 0, GL_RED, GL_UNSIGNED_BYTE, localBuffer);
	glBindTexture(GL_TEXTURE_3D, 0);
}

Texture3D::Texture3D(const std::string& filePath, int nPicX, int nPicY) : Texture(filePath),
width(0), height(0), depth(0), bpp(0) {
	stbi_set_flip_vertically_on_load(1);
	int widthPicture, heightPicture = 0;
	localBuffer = stbi_load(getFilePath().c_str(), &widthPicture, &heightPicture, &bpp, 4);

	width = widthPicture / nPicX;
	height = heightPicture / nPicY;
	depth = nPicX * nPicY;

	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_3D, ID);

	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glTexImage3D(GL_TEXTURE_3D, 0, GL_INTENSITY, width, height, depth, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, localBuffer);
	glBindTexture(GL_TEXTURE_3D, 0);
}

void Texture3D::bind(unsigned int slot) const {
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_3D, ID);
}

void Texture3D::unBind() const {
	glBindTexture(GL_TEXTURE_3D, 0);
}

Texture3D::~Texture3D() {
	if (localBuffer)
		stbi_image_free(localBuffer);
	glDeleteTextures(1, &ID);
}
