#include "Cube.h"

void Cube::CreateVertices(float width)
{
	float vertices[] = {
				width * 0.5f, width * 0.5f, width * 0.5f, 
				width * 0.5f, width * -0.5f, width * 0.5f,
				width * 0.5f, width * 0.5f, width * -0.5f,
				width * 0.5f, width * -0.5f, width * -0.5f,
				width * -0.5f, width * 0.5f, width * 0.5f,
				width * -0.5f, width * -0.5f, width * 0.5f,
				width * -0.5f, width * 0.5f, width * -0.5f,
				width * -0.5f, width * -0.5f, width * -0.5f };
	int indices[] = { 1,7,3,1,7,5,1,6,2,1,6,5,5,8,7,5,8,6,1,4,3,1,4,2,8,2,4,8,2,6 //,7,4,8,7,4,3
	};
	setVertices(vertices, 24);
	setAttributes(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	setIndices(indices, sizeof(indices) / sizeof(int));
	}

