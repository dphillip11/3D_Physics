#pragma once
#include "Shader.h"
#include "Model.h"
#include <memory>
#include <vector>
#include "Window.h"

class rayTracing: public Model
{
public:
	rayTracing();

	void shadedDraw(float time, Window window);
	
};

