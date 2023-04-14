#pragma once
#include "../Classes/rayTracing.h"
#include "../Classes/Program.h"

class Newtons_Cradle:public Program
{
public:
	rayTracing rt;

	void Setup()
	{

	}
	void Run(float time, Window window)
	{
		rt.shadedDraw(time, window);
		rt.processInput(window);
	}
};