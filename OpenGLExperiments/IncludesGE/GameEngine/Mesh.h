#pragma once

class Mesh {
protected:

	bool isSetVBO = false;
	bool isSetEBO = false;
	bool isSetVAO = false;

public:
	int indexCount = 0;
	int vertexCount = 0;
	unsigned int _VBO{ 0 }, _VAO{ 0 }, _EBO{ 0 }, _VBOnormal{ 0 }, _EBOnormal{ 0 }, _VBOtexture{ 0 }, _EBOtexture{ 0 };
	Mesh();
	void setVertices(const void* vertices, int size, const int& VAO, const int& VBO);
	void setIndices(const void* indices, int size, const int& EBO);
	void setAttributes(int vaoPos, int count, GLenum type, bool normalized, int stride, const void* pos);
	void draw(GLenum fillMode = GL_LINE, GLenum drawMode = GL_TRIANGLES);
	void Bind() const;
	void Unbind() const;

	glm::vec3 upper_bounds = glm::vec3(std::numeric_limits<float>::max());
	glm::vec3 lower_bounds = glm::vec3(-std::numeric_limits<float>::max());
};