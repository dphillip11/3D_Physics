#pragma once
#include "Model.h"
#include <vector>
#include <glm/glm/vec3.hpp>
#include "Shader.h"




class Ball : public Model
{	
	static const float X;
	static const float Z;
	static const std::vector<glm::vec3> positions;
	static const std::vector<glm::uvec3> indices;
	

public:
	Shader* sphereShader;
	glm::vec3 position = glm::vec3(0,0,0);
	glm::vec3 rotation = glm::vec3(0, 0, 0);
	float radius;

	Ball(float RADIUS) {
		usePremadeVertices(); 
		radius = RADIUS; sphereShader = new Shader("src/shaders/vertex/ball.hlsl", "src/shaders/fragment/ball.hlsl", "src/shaders/geometry/ball.hlsl");
	}
	void CreateVertices(float radius);
	void usePremadeVertices();
	void shadedDraw(GLenum fillMode = GL_FILL, GLenum drawMode = GL_TRIANGLES);
	~Ball() { delete(sphereShader);}
};

	