#pragma once
#include "Shader.h"
#include "Model.h"
#include <memory>
#include <vector>

class rayTracing: public Model
{
public:
	rayTracing()
	{
		float vertices[] = { 1,1,-1,-1,1,-1,1,1,-1,-1,-1,1 };
		shader = std::make_unique<Shader>("src/shaders/vertex/blankScreen.hlsl", "src/shaders/fragment/rayTracing.hlsl");
		setVertices(vertices, 12);
		setAttributes(0, 2, GL_FLOAT, false, 2 * sizeof(float), (void*)0);
	}
};

