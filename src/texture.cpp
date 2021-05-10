#include "texture.h"

#include <stb_image/stb_image.h>
#include <GL/glew.h>
#include <iostream>

Texture::Texture(const std::string &filepath) : filepath_(filepath)
{
	stbi_set_flip_vertically_on_load(1);
	local_buffer_ = stbi_load(filepath.c_str(), &width_, &height_, &bpp_, 4);

	glGenTextures(1, &gl_renderer_id_);
	glBindTexture(GL_TEXTURE_2D, gl_renderer_id_);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width_, height_, 0, GL_RGBA, GL_UNSIGNED_BYTE, local_buffer_);

	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{
	stbi_image_free(local_buffer_);
	glDeleteTextures(1, &gl_renderer_id_);
}

void Texture::bind(unsigned int slot)
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, gl_renderer_id_);
}

void Texture::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
