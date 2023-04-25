#include "Ball.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <vector>
#include <glm/glm/vec3.hpp>
#include <glm/glm/matrix.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

#define LOG(x) std::cout << x << std::endl;

const float Ball::X = 0.525731f;
const float Ball::Z = 0.850651f;
const std::vector<glm::vec3> Ball::_vertices =
{
glm::vec3(-X, 0.0f, Z), glm::vec3(X, 0.0f, Z), glm::vec3(-X, 0.0f, -Z), glm::vec3(X, 0.0f, -Z),
glm::vec3(0.0f, Z, X), glm::vec3(0.0f, Z, -X), glm::vec3(0.0f, -Z, X), glm::vec3(0.0f, -Z, -X),
glm::vec3(Z, X, 0.0f), glm::vec3(-Z, X, 0.0f), glm::vec3(Z, -X, 0.0f), glm::vec3(-Z, -X, 0.0f)
};

const std::vector<glm::uvec3> Ball::_indices =
{
glm::uvec3(1, 4, 0),glm::uvec3(4, 9, 0),glm::uvec3(4, 5, 9),glm::uvec3(8, 5, 4),glm::uvec3(1, 8, 4),
glm::uvec3(1, 10, 8),glm::uvec3(10, 3, 8),glm::uvec3(8, 3, 5),glm::uvec3(3, 2, 5),glm::uvec3(3, 7, 2),
glm::uvec3(3, 10, 7),glm::uvec3(10, 6, 7),glm::uvec3(6, 11, 7),glm::uvec3(6, 0, 11),glm::uvec3(6, 1, 0),
glm::uvec3(10, 1, 6),glm::uvec3(11, 0, 9),glm::uvec3(2, 11, 9),glm::uvec3(5, 2, 9),glm::uvec3(11, 2, 7)
};

Ball::Ball() 
{
	if (subdivided)
	{
		shader = std::make_unique<Shader>("Shaders/vertex/ball.hlsl", "Shaders/fragment/ball.hlsl", "Shaders/geometry/ball.hlsl");
		useSimpleVertices();
	}
	else
	{
		shader = std::make_unique<Shader>("Shaders/vertex/batchBall.hlsl", "Shaders/fragment/ball.hlsl");
		CreateVertices();
	}
}


void Ball::shadedDraw(GLenum fillMode, GLenum drawMode)
{
	shader->use();
	draw(fillMode, drawMode);
}

void Ball::CreateVertices()
{
	const float PI = (float)3.14159265;
	float* vertices = new float[NUM_SEGMENTS * NUM_SEGMENTS * 3];
	int* indices = new int[NUM_SEGMENTS * NUM_SEGMENTS * 6];

	for (int i = 0; i < NUM_SEGMENTS; i++) {
		float angle1 = (float)i / NUM_SEGMENTS * 2 *  PI;
		float y = sin(angle1);
		float r = cos(angle1);

		for (int j = 0; j < NUM_SEGMENTS; j++) {
			//this extra float sometimes causes issues with the secondary draw method
			float angle2 = (float)((float)j / NUM_SEGMENTS * 2.0 * PI);
			float x = r * cos(angle2);
			float z = r * sin(angle2);

			int vertexIndex = (i * NUM_SEGMENTS + j) * 3;
			vertices[vertexIndex + 0] = x;
			vertices[vertexIndex + 1] = y;
			vertices[vertexIndex + 2] = z;
		}
	}

	int index = 0;
	for (int i = 0; i < NUM_SEGMENTS - 1; i++) {
		for (int j = 0; j < NUM_SEGMENTS; j++) {
			indices[index++] = i * NUM_SEGMENTS + j;
			indices[index++] = (i + 1) * NUM_SEGMENTS + j;
			indices[index++] = (i + 1) * NUM_SEGMENTS + (j + 1) % NUM_SEGMENTS;

			indices[index++] = i * NUM_SEGMENTS + j;
			indices[index++] = (i + 1) * NUM_SEGMENTS + (j + 1) % NUM_SEGMENTS;
			indices[index++] = i * NUM_SEGMENTS + (j + 1) % NUM_SEGMENTS;
		}
	}

	setVertices(vertices, NUM_SEGMENTS * NUM_SEGMENTS * 3, _VAO, _VBO);
	delete[](vertices);
	setIndices(indices, NUM_SEGMENTS * NUM_SEGMENTS * 6, _EBO);
	delete[](indices);
	setAttributes(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));


}

void Ball::useSimpleVertices()
{
	setVertices(&_vertices[0], (int)_vertices.size() * 3, _VAO, _VBO);
	setIndices(&_indices[0], (int)_indices.size() * 3, _EBO);
	setAttributes(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));
}




