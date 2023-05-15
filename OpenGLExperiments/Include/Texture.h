#pragma once
#include "PCH/pch.h"

class Texture
{
	int width{ 1 }, height{ 1 }, nrChannels{ 1 };
public:
	unsigned int texture;

	Texture();
	void setParameters(GLenum target = GL_TEXTURE_2D, GLenum wrap = GL_TEXTURE_WRAP_S, GLint repeat = GL_REPEAT, GLint filter = GL_LINEAR);
	void loadImage(const char* filepath, GLenum format = GL_RGB, bool flipped = false);
	void bind();
};

