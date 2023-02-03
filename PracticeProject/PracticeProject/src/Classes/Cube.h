#pragma once
#include "Model.h"

class Cube:public Model
{
public:
	Cube(){}
	Cube(float width) {CreateVertices(width); }
	void CreateVertices(float width);
};

