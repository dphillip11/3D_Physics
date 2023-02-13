#pragma once
#include "Ball.h"
#include "Manager.h"

class BallManager:public Manager
{
	

public:
	std::unique_ptr<Ball> ball;

	void update(float deltaTime);
	void spawnBalls(int n);
	void drawBalls(glm::mat4 view, glm::mat4 projection);

	BallManager() : ball(std::make_unique<Ball>()) {}

	void resolveCollisions();
	void resolveCollisions_no_buckets();

	void spawnFlattenedBalls(int n);

};

