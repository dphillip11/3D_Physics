#pragma once
#include "../Classes/rayTracing.h"
#include "../InputHandlers/NewtonsCradleInput.h"

class Newtons_Cradle:public Program
{
public:
	rayTracing rt;
	float time = 0;
	NewtonsCradleInput inputHandler{&rt};

	void Setup()
	{

	}
	void Run(float deltaTime)
	{
		time += deltaTime;
		rt.shadedDraw(time, *Window::instance);
		inputHandler.processInput();
	}

	InputObserver* getInputHandler()
	{
		return &inputHandler;
	}
};