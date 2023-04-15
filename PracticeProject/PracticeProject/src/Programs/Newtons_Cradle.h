#pragma once
#include "../Classes/rayTracing.h"

class Newtons_Cradle:public Program
{
public:
	rayTracing rt;

	void Setup(Camera* camera)
	{

	}
	void Run(float time, Window window)
	{
		rt.shadedDraw(time, window);
		rt.processInput(window);
	}
};