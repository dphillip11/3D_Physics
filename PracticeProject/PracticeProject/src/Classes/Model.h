#pragma once
#include <glad/glad.h>
#include <glm/glm/matrix.hpp>

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
	glm::mat4 transform = glm::mat4(1);
	
	Model();
	void setVertices(const void* vertices,int size);
	void setIndices(const void* indices, int size);
	void setAttributes(int vaoPos, int count, GLenum type, bool normalized, int stride, const void* pos);
	void draw(GLenum fillMode = GL_FILL, GLenum drawMode = GL_TRIANGLES);
};

