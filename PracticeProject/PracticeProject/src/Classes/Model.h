#pragma once
#include <glad/glad.h>
#include <glm/glm/matrix.hpp>
#include "Shader.h"
#include <memory>
#include <vector>

class Model
{
protected:
	
	bool isSetVBO = false;
	bool isSetEBO = false;
	bool isSetVAO = false;
	int indexCount = 0;
	int vertexCount = 0;

public:

	unsigned int _VBO, _VAO, _EBO, _VBOnormal, _EBOnormal;
	glm::mat4 transform = glm::mat4(1);
	std::unique_ptr<Shader> shader;
	Model();
	void setVertices(const void* vertices,int size,const int &VAO,const int &VBO);
	void setIndices(const void* indices, int size,const int &EBO);
	void setAttributes(int vaoPos, int count, GLenum type, bool normalized, int stride, const void* pos);
	void draw(GLenum fillMode = GL_FILL, GLenum drawMode = GL_TRIANGLES);
};

