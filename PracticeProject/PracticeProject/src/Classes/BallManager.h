#pragma once
#include "Ball.h"
#include "Manager.h"

class BallManager:public Manager
{
	

public:

	void update(float deltaTime);

	BallManager() { object = std::make_unique<Ball>(); }

	void resolveCollisions();
	void resolveCollisions_no_buckets();


};

