#include "Texture.h"
#include "stb_image.h"
#include <glad/glad.h>
#include <iostream>

Texture::Texture()
{
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
}

void Texture::setParameters(GLenum target , GLenum wrap, GLint repeat, GLint filter)
{
	glTexParameteri(target, GL_TEXTURE_WRAP_S, wrap);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(target, GL_TEXTURE_WRAP_T, wrap);
	glTexParameteri(target, GL_TEXTURE_MIN_FILTER, filter);
	glTexParameteri(target, GL_TEXTURE_MAG_FILTER, filter);
}

void Texture::loadImage(const char* filepath, GLenum format, bool flipped)
{
    // load image, create texture and generate mipmaps
    stbi_set_flip_vertically_on_load(flipped); // tell stb_image.h to flip loaded texture's on the y-axis.
    unsigned char* data = stbi_load(filepath, &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}

void Texture::bind()
{
    glBindTexture(GL_TEXTURE_2D, texture);
}