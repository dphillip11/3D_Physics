#pragma once

struct face {
	int vIndex;
	int tIndex;
	int nIndex;
};

class obj
{
public:
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> textureMap;
	std::vector<glm::vec3> normalMap;

	std::vector<int> vertexIndices;
	std::vector<int> normalIndices;
	std::vector<int> textureIndices;

	glm::vec3 upper_bounds = glm::vec3(-std::numeric_limits<float>::max());
	glm::vec3 lower_bounds = glm::vec3(std::numeric_limits<float>::max());

	face cursor = { 0,0,0 };
	std::vector<face> buffer;
	std::vector<face> stack;

	// currently only loads face elements composed of triangles
	void read(std::string filepath);

	void convertToTriangles(std::vector<face>& face_elements);

	void pushBufferToStack();
	void splitStackIntoIndices();

	std::vector<glm::vec3> unravelIndices(std::vector<glm::vec3>& values, std::vector<int>& indices);
};



