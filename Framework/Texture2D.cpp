#include "Texture2D.h"
#include <GL/glew.h>
#include "stb_image.h"

Texture2D::Texture2D(const std::string& filePath) : Texture(filePath),
width(0), height(0), bpp(0) {
	stbi_set_flip_vertically_on_load(1);
	localBuffer = stbi_load(getFilePath().c_str(), &width, &height, &bpp, 4);

	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::bind(unsigned int slot) const {
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture2D::unBind() const {
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture2D::~Texture2D() {
	if (localBuffer)
		stbi_image_free(localBuffer);
	glDeleteTextures(1, &ID);
	
}
