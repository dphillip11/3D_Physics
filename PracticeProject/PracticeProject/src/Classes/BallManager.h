#pragma once
#include "Ball.h"


class BallManager
{
	std::unique_ptr<Ball> ball;
	std::vector<glm::vec3> position;
	std::vector<glm::vec3> velocity;
	std::vector<float> radius;
	const float boundarySize = 100;
	const float maxSpeed = 20;
	const float maxRadius = 5;

	int ballCount = 0;

	void updatePositions(float deltaTime);
	void spawnBalls(int n);
	void drawBalls();
	float randomVal(float magnitude, bool onlyPositive = false);
	glm::vec3 randomVec3(float magnitude);
	BallManager() : ball(std::make_unique<Ball>()) {}

};

