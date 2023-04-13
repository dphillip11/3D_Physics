#include "obj.h"
#include <iostream>
#include <fstream>
#include <sstream>




void obj::read(std::string filepath)
{
	std::ifstream infile(filepath);
	if (!infile.is_open()) {
		std::cout << "Unable to open file: " << filepath << "\n";
		return;
	}

	std::string line;
	while (getline(infile, line)) 
	{
		std::istringstream iss(line);
		std::string keyword;
		iss >> keyword;
		if (keyword == "v") {
			glm::vec3 v;
			iss >> v.x >> v.y >> v.z;
			vertices.push_back(v);
		}
		if (keyword == "vn") {
			glm::vec3 vn;
			iss >> vn.x >> vn.y >> vn.z;
			normalMap.push_back(vn);
		}
		if (keyword == "vt") {
			glm::vec3 vt;
			iss >> vt.x  >> vt.y >> vt.z;
			textureMap.push_back(vt);
		}
		if (keyword == "f")
			//currently assumes triangular vertices, needs to be updated for polygonal elements
		{
			std::string vertexIndexString;
			std::string textureIndexString;
			std::string normalIndexString;

		// Parse vertex index, texture index, and normal index from the line
			std::vector<face> face_elements;
			while (iss >> vertexIndexString) {
				std::istringstream vertexIndexStream(vertexIndexString);

				int vertexIndex = 1;
				int textureIndex = 1;
				int normalIndex = 1;

				// Parse vertex index, texture index, and normal index from the vertex index string
				vertexIndexStream >> vertexIndex;
				if (vertexIndexStream.peek() == '/') {
					vertexIndexStream.ignore();
					if (vertexIndexStream.peek() != '/') {
						std::getline(vertexIndexStream, textureIndexString, '/');
						std::istringstream textureIndexStream(textureIndexString);
						textureIndexStream >> textureIndex;
					}
					if (vertexIndexStream.peek() == '/') {
						vertexIndexStream.ignore();
						std::getline(vertexIndexStream, normalIndexString, '/');
						std::istringstream normalIndexStream(normalIndexString);
						normalIndexStream >> normalIndex;
					}
				}
				face_elements.push_back({vertexIndex - 1,textureIndex - 1,normalIndex - 1 });
			}
			convertToTriangles(face_elements);
		}
	}

}

void obj::convertToTriangles(std::vector<face>& face_elements)
{
	int number_of_vertices = face_elements.size();
	//if triangles cannot be formed store vertices
	if (number_of_vertices < 3)
	{
		for (face face_element : face_elements)
		{
			// Store vertex index, texture index, and normal index in separate vectors
			vertexIndices.push_back(face_element.vIndex);
			textureIndices.push_back(face_element.tIndex);
			normalIndices.push_back(face_element.nIndex);
		}
	}
	else
	{
		//store indices per triangle using the first vertex as a fanning point
		for (int i = 0; i < number_of_vertices - 2; i++)
		{
			//fanning point
			vertexIndices.push_back(face_elements[0].vIndex);
			textureIndices.push_back(face_elements[0].tIndex);
			normalIndices.push_back(face_elements[0].nIndex);

			//second vertex
			vertexIndices.push_back(face_elements[i+1].vIndex);
			textureIndices.push_back(face_elements[i+1].tIndex);
			normalIndices.push_back(face_elements[i+1].nIndex);

			//third vertex
			vertexIndices.push_back(face_elements[i+2].vIndex);
			textureIndices.push_back(face_elements[i+2].tIndex);
			normalIndices.push_back(face_elements[i+2].nIndex);
		}
	}


}

std::vector<glm::vec3> obj::unravelIndices(std::vector<glm::vec3>& values, std::vector<int>& indices)
{
	std::vector<glm::vec3> tempValues;
	for (int index : indices)
	{
		tempValues.push_back(values[index]);
	}
	return tempValues;
}
