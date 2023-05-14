#include "pch.h"
#include "Model.h"

Model::Model() : isSetEBO(false), isSetVBO(false), isSetVAO(false) {
	glGenVertexArrays(1, &_VAO);
	glGenBuffers(1, &_VBO);
	glGenBuffers(1, &_VBOnormal);
	glGenBuffers(1, &_VBOtexture);
	glGenBuffers(1, &_EBO);
}

void Model::setVertices(const void* vertices, int size, const int& VAO, const int& VBO) {
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), vertices, GL_STATIC_DRAW);
	vertexCount = size;
	isSetVBO = true;
}
void Model::setIndices(const void* indices, int size, const int& EBO) {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(int), indices, GL_STATIC_DRAW);
	indexCount = size;
	isSetEBO = true;
}

void Model::setAttributes(int vaoPos, int count, GLenum type, bool normalized, int stride, const void* pos)
{
	glEnableVertexAttribArray(vaoPos);
	glVertexAttribPointer(vaoPos, count, type, normalized ? GL_TRUE : GL_FALSE, stride, pos);
	isSetVAO = true;
}

void Model::draw(GLenum fillMode, GLenum drawMode) {
	//can take draw mode GL_POINTS, GL_TRIANGLES and GL_LINE_STRIP
	//can take fill mode GL_LINE, GL_FILL
	glPolygonMode(GL_FRONT_AND_BACK, fillMode);
	if (isSetVAO && isSetEBO && isSetVBO)
	{
		glBindVertexArray(_VAO);
		glDrawElements(drawMode, indexCount, GL_UNSIGNED_INT, 0);
	}
	else if (isSetVAO && isSetVBO)
	{
		glBindVertexArray(_VAO);
		glDrawArrays(drawMode, 0, vertexCount);
	}

}

