#include "pch.h"
#include "rayTracing.h"

rayTracing::rayTracing()
{
	float vertices[] = { 1,1,-1,-1,1,-1,1,1,-1,-1,-1,1 };
	shader = std::make_unique<Shader>("shaders/vertex/blankScreen.hlsl", "shaders/fragment/rayTracing.hlsl");
	setVertices(vertices, 12, _VAO, _VBO);
	setAttributes(0, 2, GL_FLOAT, false, 2 * sizeof(float), (void*)0);
}

void rayTracing::shadedDraw(float time, Window window)
{

	shader->use();
	shader->setFloat("iTime", time);
	shader->setVec3("iResolution", glm::vec3(window._width, window._height, 0));

	draw();
}