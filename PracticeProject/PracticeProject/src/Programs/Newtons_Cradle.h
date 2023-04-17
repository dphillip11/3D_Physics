#pragma once
#include "../Classes/rayTracing.h"

class Newtons_Cradle:public Program
{
public:
	rayTracing rt;
	float time = 0;

	void Setup()
	{

	}
	void Run(float deltaTime)
	{
		time += deltaTime;
		rt.shadedDraw(time, *Window::instance);
		rt.processInput();
	}

	InputObserver* getInputHandler()
	{
		return nullptr;
	}
};