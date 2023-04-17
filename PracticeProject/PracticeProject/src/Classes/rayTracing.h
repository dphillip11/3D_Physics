#pragma once
#include "Shader.h"
#include "Model.h"
#include <memory>
#include <vector>
#include "Window.h"

class rayTracing: public Model
{
public:
	float cam_depth = 0.5;
	float cam_y = 10;
	rayTracing()
	{
		float vertices[] = { 1,1,-1,-1,1,-1,1,1,-1,-1,-1,1 };
		shader = std::make_unique<Shader>("src/shaders/vertex/blankScreen.hlsl", "src/shaders/fragment/rayTracing.hlsl");
		setVertices(vertices, 12, _VAO, _VBO);
		setAttributes(0, 2, GL_FLOAT, false, 2 * sizeof(float), (void*)0);
	}
	void shadedDraw(float time, Window window)
	{
		
		shader->use();
		processInput();
		shader->setFloat("cam_y", cam_y);
		shader->setFloat("iTime", time);
		shader->setVec3("iResolution", glm::vec3(window._width, window._height, 0));
		
		draw();
	}
	void processInput()
	{
		shader->setVec3("iMouse", glm::vec3(-Window::instance->input->mouseX, -Window::instance->input->mouseY, 0));
		cam_depth = (float)fmax(cam_depth + Window::instance->input->scrollOffset * 0.05f, 0.1);
		shader->setFloat("cam_depth", cam_depth);
		while (!Window::instance->input->input.empty())
		{
			if (Window::instance->input->input.front() == KEYS::UP)
			{
				cam_y += (float)0.1;
				cam_y = (float)fmin(fmax(0.1f, cam_y), 30);
				Window::instance->input->input.pop();
			}
			else if (Window::instance->input->input.front() == KEYS::DOWN)
			{
				cam_y -= (float)0.1;
				cam_y = (float)fmin(fmax(0.1, cam_y), 30);
				Window::instance->input->input.pop();
			}
			else
				Window::instance->input->input.pop();
		}
	}
	
};

