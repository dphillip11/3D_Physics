#pragma once
#include <glfw3.h>

class Texture
{
	int width, height, nrChannels;
public:
	unsigned int texture;
	
	Texture();
	void setParameters(GLenum target = GL_TEXTURE_2D, GLenum wrap = GL_TEXTURE_WRAP_S, GLint repeat = GL_REPEAT, GLint filter = GL_LINEAR);
	void loadImage(const char* filepath, GLenum format = GL_RGB, bool flipped = false);
	void bind();
};

