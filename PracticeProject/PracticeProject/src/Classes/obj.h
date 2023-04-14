#pragma once
#include <vector>
#include <string>
#include <glm/glm/vec3.hpp>
#include <glm/glm/vec2.hpp>

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

	// currently only loads face elements composed of triangles
	void read(std::string filepath);

	void convertToTriangles(std::vector<face>& face_elements);

	std::vector<glm::vec3> unravelIndices(std::vector<glm::vec3>& values, std::vector<int>& indices);
};



