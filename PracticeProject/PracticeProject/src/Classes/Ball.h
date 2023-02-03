#pragma once
#include "Model.h"
#include "../Header.hpp"


class Ball : public Model
{
public:
	Vector3 position = { 0,0,0 };

	Ball() {};
	void CreateVertices(float radius);
};
	