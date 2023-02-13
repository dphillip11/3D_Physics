#pragma once
#include "Cube.h"
#include "Manager.h"


class CubeManager: public Manager
{

public:

	int ballCount = 0;

	void update(float deltaTime) 
	{
		updatePositions(deltaTime);
	}
	CubeManager() {
		object = std::make_unique<Cube>(); }

};

