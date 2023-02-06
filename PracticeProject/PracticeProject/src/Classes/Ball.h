#pragma once
#include "Model.h"
#include "Vector3.h"


class Ball : public Model
{
public:
	Vector3 position = { 0,0,0 };

	Ball() {};
	Ball(float radius) { CreateVertices(radius); }
	void CreateVertices(float radius);
};
	