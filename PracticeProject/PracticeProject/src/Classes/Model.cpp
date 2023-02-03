#include "Model.h"
//#include "glad/glad.h"
//#include <GLFW/glfw3.h>

Model::Model(): isSetEBO(false), isSetVBO(false), isSetVAO(false) {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
}

void Model::setVertices(const float* vertices, int size) {
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), vertices, GL_STATIC_DRAW);
	vertexCount = size;
	isSetVBO = true;
}
void Model::setIndices(const int* indices, int size) {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(int), indices, GL_STATIC_DRAW);
	indexCount = size;
	isSetEBO = true;
}
void Model::setAttributes(int vaoPos, int count, GLenum type, GLboolean normalized, int stride, const void* pos)
{
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindVertexArray(VAO);
	//glVertexAttribPointer(vaoPos, count, type, normalized, stride, pos);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	isSetVAO = true;
}

void Model::draw(GLenum fillMode, GLenum drawMode) {
	//can take draw mode GL_POINTS, GL_TRIANGLES and GL_LINE_STRIP
	//can take fill mode GL_LINE, GL_FILL
	glPolygonMode(GL_FRONT_AND_BACK, fillMode);
	if (isSetVAO && isSetEBO && isSetVBO)
	{
		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);	
		glDrawElements(drawMode, indexCount, GL_UNSIGNED_INT, 0);//9 vertices
	}
	else if (isSetVAO && isSetVBO)
	{
		glBindVertexArray(VAO);
		glDrawArrays(drawMode,0, vertexCount);
	}

}
