#pragma once
#include "Model.h"
#include <vector>
#include <glm/glm/vec3.hpp>
#include "Shader.h"
#include <memory>




class Ball : public Model
{	
	static const float X;
	static const float Z;
	static const std::vector<glm::vec3> _vertices;
	static const std::vector<glm::uvec3> _indices;
	//using subdivision improves memory usage, whereas not using it improves computational load on rendering
	static const int subdivided = false;
	static const int NUM_SEGMENTS = 40;
	

public:

	Ball()
	{
		if (subdivided)
		{
			shader = std::make_unique<Shader>("src/shaders/vertex/ball.hlsl", "src/shaders/fragment/ball.hlsl", "src/shaders/geometry/ball.hlsl");
			useSimpleVertices();
		}
		else
		{
			shader = std::make_unique<Shader>("src/shaders/vertex/ballS.hlsl", "src/shaders/fragment/ball.hlsl");
			CreateVertices();
		}
	}
	void CreateVertices();
	void useSimpleVertices();
	void shadedDraw(GLenum fillMode = GL_FILL, GLenum drawMode = GL_TRIANGLES);
};

	