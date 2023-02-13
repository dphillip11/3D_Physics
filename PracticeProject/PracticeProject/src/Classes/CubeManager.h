#pragma once
#include "Cube.h"
#include "Manager.h"


class CubeManager: public Manager
{

public:
	std::unique_ptr<Cube> cube;
	
	int ballCount = 0;

	void spawnCubes(int n);
	void drawCubes(glm::mat4 view, glm::mat4 projection);

	CubeManager() : cube(std::make_unique<Cube>()) {}

	//void resolveCollisions();
	//void resolveCollisions_no_buckets();

};

