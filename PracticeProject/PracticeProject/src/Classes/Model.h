#pragma once
#include "glad/glad.h"

class Model
{
protected:
	unsigned int VBO, VAO, EBO;
	bool isSetVBO = false;
	bool isSetEBO = false;
	bool isSetVAO = false;
	int indexCount = 0;
	int vertexCount = 0;

public:
	
	Model();
	void setVertices(const void* vertices,int size);
	void setIndices(const void* indices, int size);
	void setAttributes(int vaoPos, int count, GLenum type, bool normalized, int stride, const void* pos);
	void draw(GLenum fillMode = GL_FILL, GLenum drawMode = GL_TRIANGLES);
};
