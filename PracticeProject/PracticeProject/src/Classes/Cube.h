#pragma once
#include "Model.h"
#include "Shader.h"
#include <memory>

class Cube:public Model
{
public:


	Cube()
	{
		CreateVertices();
		shader = std::make_unique<Shader>("src/shaders/vertex/ballS.hlsl", "src/shaders/fragment/ball.hlsl");
	}

	void CreateVertices();
	void shadedDraw(GLenum fillMode = GL_FILL, GLenum drawMode = GL_TRIANGLES);
};



