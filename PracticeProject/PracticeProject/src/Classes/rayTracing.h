#pragma once
#include "Shader.h"
#include "Model.h"
#include <memory>
#include <vector>

class rayTracing: public Model
{
public:
	Texture marble;
	float cam_depth = 0.5;
	float cam_y = 10;
	rayTracing()
	{
		float vertices[] = { 1,1,-1,-1,1,-1,1,1,-1,-1,-1,1 };
		shader = std::make_unique<Shader>("src/shaders/vertex/blankScreen.hlsl", "src/shaders/fragment/rayTracing.hlsl");
		setVertices(vertices, 12);
		setAttributes(0, 2, GL_FLOAT, false, 2 * sizeof(float), (void*)0);
		marble = Texture();
		marble.loadImage("src/Textures/marble.jpg");
		marble.bind();
	}
	void shadedDraw(float time, Window window)
	{
		
		shader->use();
		processInput(window);
		marble.bind();
		shader->setFloat("cam_y", cam_y);
		shader->setFloat("iTime", time);
		shader->setVec3("iResolution", glm::vec3(window._width, window._height, 0));
		
		draw();
	}
	void processInput(Window window)
	{
		shader->setVec3("iMouse", glm::vec3(-window.input->mouseX, -window.input->mouseY, 0));
		cam_depth = fmax(cam_depth + window.input->scrollOffset * 0.05f, 0.1);
		shader->setFloat("cam_depth", cam_depth);
		while (!window.input->input.empty())
		{
			if (window.input->input.front() == KEYS::UP)
			{
				cam_y += 0.1;
				cam_y = fmin(fmax(0.1, cam_y), 30);
				window.input->input.pop();
			}
			else if (window.input->input.front() == KEYS::DOWN)
			{
				cam_y -= 0.1;
				cam_y = fmin(fmax(0.1, cam_y), 30);
				window.input->input.pop();
			}
			else
				window.input->input.pop();
		}
	}
	
};

