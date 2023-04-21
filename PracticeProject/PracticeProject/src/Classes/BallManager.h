#pragma once
#include "Ball.h"
#include "Manager.h"

class BallManager:public Manager
{
	

public:
	int max_bucket_size = 100;
	void update(float deltaTime);

	BallManager() { object = std::make_unique<Ball>(); }
	//resolve single collision
	void resolveCollision(int ID1, int ID2);
	//fixed buckets
	void resolveCollisions_fixed_buckets();
	//recursively assigned buckets
	void resolveCollisions_dynamic_buckets();
	void resolveCollisionsRecursive(int* bucket, int size, const glm::vec2& x_range, const glm::vec2& z_range);
	//single array
	void resolveCollisions_no_buckets();


};

