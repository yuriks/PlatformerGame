#include "texture.hpp"

#include "stb_image.h"
#include "GL3/gl3w.h"
#include <memory>
#include <cassert>

gl::Texture loadTexture(int* out_width, int* out_height, const char* filename, bool premultiply) {
	gl::Texture main_texture;
	glGenTextures(1, &main_texture.name);

	glBindTexture(GL_TEXTURE_2D, main_texture.name);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	int width, height, comp;
	auto data = std::unique_ptr<unsigned char[], void(*)(void*)>(
		stbi_load(filename, &width, &height, &comp, 4), &stbi_image_free);
	if (data == nullptr)
		return gl::Texture();

	if (premultiply) {
		unsigned int size = width * height;

		for (unsigned int i = 0; i < size; ++i) {
			unsigned char alpha = data[i*4 + 3];
			for (unsigned int j = 0; j < 3; ++j) {
				data[i*4 + j] = data[i*4 + j] * alpha / 255;
			}
		}
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data.get());

	*out_width = width;
	*out_height = height;
	return main_texture;
}

TextureInfo loadTexture(const char* filename, bool premultiply) {
	TextureInfo tex;
	tex.handle = loadTexture(&tex.width, &tex.height, filename, premultiply);
	assert(tex.handle.name != 0);
	return tex;
}
