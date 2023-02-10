#pragma once
#include "Model.h"
#include <vector>
#include "../Libraries/glm/glm/vec3.hpp"
#include "Shader.h"
#include <memory>




class Ball : public Model
{	
	static const float X;
	static const float Z;
	static const std::vector<glm::vec3> _vertices;
	static const std::vector<glm::uvec3> _indices;
	

public:
	std::unique_ptr<Shader> sphereShader;

	Ball()
	{
		sphereShader = std::make_unique<Shader>("src/shaders/vertex/ball.hlsl", "src/shaders/fragment/ball.hlsl", "src/shaders/geometry/ball.hlsl");
		useSimpleVertices(); 
	}
	void CreateVertices(float radius);
	void useSimpleVertices();
	void shadedDraw(GLenum fillMode = GL_FILL, GLenum drawMode = GL_TRIANGLES);
};

	