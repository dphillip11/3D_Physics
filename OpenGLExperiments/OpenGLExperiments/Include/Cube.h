#pragma once
#include "Model.h"
#include "Shader.h"


class Cube :public Model
{
public:


	Cube();

	void CreateVertices();
	void shadedDraw(GLenum fillMode = GL_FILL, GLenum drawMode = GL_TRIANGLES);
};



