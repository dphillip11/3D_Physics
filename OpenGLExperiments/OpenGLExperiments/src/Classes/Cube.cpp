#include "Cube.h"
#include <iostream>


void Cube::CreateVertices()
{
	float vertices[] = {
				 0.5f,  0.5f,  0.5f, 
				 0.5f,  -0.5f,  0.5f,
				 0.5f,  0.5f,  -0.5f,
				 0.5f,  -0.5f,  -0.5f,
				 -0.5f,  0.5f,  0.5f,
				 -0.5f,  -0.5f,  0.5f,
				 -0.5f,  0.5f,  -0.5f,
				 -0.5f,  -0.5f,  -0.5f };
	int indices[] = { 0, 6, 2, 0, 6, 4, 0, 5, 1, 0, 5, 4, 4, 7, 6, 4, 7, 5, 0, 3, 2, 0, 3, 1, 7, 1, 3, 7, 1, 5, 6, 3, 7, 6, 3, 2
	};


	setVertices(vertices,sizeof(vertices)/sizeof(float), _VAO, _VBO);
	setAttributes(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	setIndices(indices, sizeof(indices) / sizeof(int), _EBO);
	}

void Cube::shadedDraw(GLenum fillMode, GLenum drawMode)
{
	shader->use();
	draw(fillMode, drawMode);
}

