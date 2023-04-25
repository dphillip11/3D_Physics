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

	buffer.clear();
	stack.clear();
	cursor = { 0,0,0 };

	while (getline(infile, line)) 
	{
		std::istringstream iss(line);
		std::string keyword;
		iss >> keyword;
		if (keyword == "#") {
			iss >> keyword;
			if (keyword == "object")
			{
				pushBufferToStack();
			}
		}
		else if (keyword == "v") {
			glm::vec3 v;
			iss >> v.x >> v.y >> v.z;
			vertices.push_back(v);
		}
		else if (keyword == "vn") {
			glm::vec3 vn;
			iss >> vn.x >> vn.y >> vn.z;
			normalMap.push_back(vn);
		}
		else if (keyword == "vt") {
			glm::vec3 vt(0);
			iss >> vt.x  >> vt.y;
			textureMap.push_back(vt);
		}
		else if (keyword == "f")
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
					std::getline(vertexIndexStream, textureIndexString, '/');
					std::istringstream textureIndexStream(textureIndexString);
					textureIndexStream >> textureIndex;
					std::getline(vertexIndexStream, normalIndexString, '/');
					std::istringstream normalIndexStream(normalIndexString);
					normalIndexStream >> normalIndex;
				}
				else {
					// If no texture index, then no normal index as well
					normalIndex = vertexIndex;
				}
				face_elements.push_back({ vertexIndex, textureIndex, normalIndex});
			}
			//triangulate face and add indices to buffer
			convertToTriangles(face_elements);
		}
		
	}
	pushBufferToStack();
	splitStackIntoIndices();
}

void obj::splitStackIntoIndices()
{
	for (face index : stack)
	{
		vertexIndices.push_back(index.vIndex);
		textureIndices.push_back(index.tIndex);
		normalIndices.push_back(index.nIndex);
	}
	stack.clear();
}

void obj::pushBufferToStack()
{
	//sort buffer
	for (face& index : buffer)
	{
		//swap negative values for positive, zero index positive values
		index.vIndex = (index.vIndex < 0) ? ((int)vertices.size() - cursor.vIndex + index.vIndex ) : index.vIndex - 1;
		index.tIndex = (index.tIndex < 0) ? ((int)textureMap.size() - cursor.tIndex + index.tIndex ) : index.tIndex - 1;
		index.nIndex = (index.nIndex < 0) ? ((int)normalMap.size() - cursor.nIndex + index.nIndex ) : index.nIndex - 1;
		//shift to the right for existing vertices
		index = { index.vIndex + cursor.vIndex, index.tIndex + cursor.tIndex, index.nIndex + cursor.nIndex };
		//add index to stack of face elements
		stack.push_back(index);
	}
	//move cursor
	cursor = { (int)vertices.size(), (int)textureMap.size(), (int)normalMap.size() };
	//clear buffer
	buffer.clear();
	

}

void obj::convertToTriangles(std::vector<face>& face_elements)
{
	int number_of_vertices = (int)face_elements.size();
	//if triangles cannot be formed store vertices
	if (number_of_vertices <= 3)
	{
		for (face face_element : face_elements)
		{
			// Store vertex index, texture index, and normal index in separate vectors
			buffer.push_back(face_element);
		}
	}
	else
	{
		//store indices per triangle using the first vertex as a fanning point
		for (int i = 0; i < number_of_vertices - 2; i++)
		{
			//fanning point
			buffer.push_back(face_elements[0]);
			//second vertex
			buffer.push_back(face_elements[i+1]);
			//third vertex
			buffer.push_back(face_elements[i+2]);

		}
	}


}

std::vector<glm::vec3> obj::unravelIndices(std::vector<glm::vec3>& values, std::vector<int>& indices)
{
	std::vector<glm::vec3> tempValues;
	if (values.size() == 0)
		return tempValues;
	for (int i=0 ; i < indices.size(); i++)
	{
		int index = indices[i];
		tempValues.push_back(values[index]);
	}
	return tempValues;
}
