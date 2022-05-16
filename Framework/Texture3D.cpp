#include "Texture3D.h"
#include <GL/glew.h>
#include <vector>
#include "stb_image.h"

Texture3D::Texture3D(const std::string& filePath, int width, int height, int depth): Texture(filePath), 
width(width), height(height), depth(depth), bpp(0) {
	int widthPicture, heightPicture = 0;
	localBuffer = stbi_load(getFilePath().c_str(), &widthPicture, &heightPicture, &bpp, 4);
	std::vector<uint8_t> data3d(256*256*256);
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			for (int k = 0; k < depth; k++) {
				char v = localBuffer[(int)(i + 4096 * j + 256 * (k % 16) + 4096 * 256 * floor(float(k) / 16.0f)) * 4];
				data3d[i + 256 * (j + 256 * k)] = v;
			}
		}
	}

	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_3D, ID);

	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage3D(GL_TEXTURE_3D, 0, GL_R8, width, height, depth, 0, GL_RED, GL_UNSIGNED_BYTE, data3d.data());
	glBindTexture(GL_TEXTURE_3D, 0);
}

Texture3D::Texture3D(const std::string& filePath, int nPicX, int nPicY) : Texture(filePath),
width(0), height(0), depth(0), bpp(0) {
	int widthPicture, heightPicture = 0;
	localBuffer = stbi_load(getFilePath().c_str(), &widthPicture, &heightPicture, &bpp, 4);

	width = widthPicture / nPicX;
	height = heightPicture / nPicY;
	depth = nPicX * nPicY;

	localBuffer = stbi_load(getFilePath().c_str(), &widthPicture, &heightPicture, &bpp, 4);
	std::vector<uint8_t> data3d(256 * 256 * 256);
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			for (int k = 0; k < depth; k++) {
				char v = localBuffer[(int)(i + 4096 * j + 256 * (k % 16) + 4096 * 256 * floor(float(k) / 16.0f)) * 4];
				data3d[i + 256 * (j + 256 * k)] = v;
			}
		}
	}

	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_3D, ID);

	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage3D(GL_TEXTURE_3D, 0, GL_R8, width, height, depth, 0, GL_RED, GL_UNSIGNED_BYTE, data3d.data());
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
