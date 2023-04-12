#pragma once
#include <vector>
#include <string>

struct face {
	int vIndex;
	int tIndex;
	int nIndex;
};

class obj
{
public:
	std::vector<float> vertices;
	int totalV = 0;
	std::vector<float> textureMap;
	int totalT = 0;
	std::vector<float> normalMap;
	int totalN = 0;

	std::vector<int> vertexIndices;
	std::vector<int> normalIndices;
	std::vector<int> textureIndices;

	// currently only loads face elements composed of triangles
	void read(std::string filepath);

	void convertToTriangles(std::vector<face>& face_elements);
};



