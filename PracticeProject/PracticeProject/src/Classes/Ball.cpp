#include "Ball.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <vector>
#include "Vector3.h"

#define LOG(x) std::cout << x << std::endl;



void Ball::CreateVertices(float radius)
{
	float vertices[192];
	for (int i = 0; i < 8; i++)
	{
		float angle1 = (2 * i * (float)M_PI) / 8;
		for (int j = 0; j < 8; j++)
		{
			float angle2 = (2 * j * (float)M_PI) / 8;
			vertices[i * 24 + j * 3]  = radius * (float)sin(angle1) * (float)cos(angle2);
			vertices[i * 24 + j * 3 + 1] = radius * (float)sin(angle1) * (float)sin(angle2);
			vertices[i * 24 + j * 3 + 2] = radius * (float)cos(angle1);
		}
	}
	int indices[294];
	int n_segments = 8;
	int n_points = 64;
	int index = 0;
		for (int i = 0; i < n_points - n_segments; i++) {
			if ((i + 1) % n_segments != 0) {
				indices[index] = (i);
				index++;
				indices[index] = (i + 1);
				index++;
				indices[index] = (i + n_segments);
				index++;
				indices[index] = (i + 1);
				index++;
				indices[index] = (i + n_segments + 1);
				index++;
				indices[index] = (i + n_segments);
				index++;
			}
		}
		
	setVertices(vertices, 192);
	setIndices(indices, 294);
	setAttributes(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));
}





