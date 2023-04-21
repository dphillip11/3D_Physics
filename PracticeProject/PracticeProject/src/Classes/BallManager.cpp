#include "BallManager.h"
#include <glm/glm/gtc/matrix_transform.hpp>
#include <ppl.h>
#include <glm/glm/geometric.hpp>
#include <numeric>

void BallManager::resolveCollisions_no_buckets()
{
		for (int i = 0; i < count; i++)
		{
			for (int j = i + 1; j < count; j++)
			{
				resolveCollision(i, j);
			}
		}
}

void BallManager::resolveCollision(int ID1, int ID2)
{
	float sumOfRadii = halfWidth[ID1] + halfWidth[ID2];
	float x_diff = position[ID1].x - position[ID2].x;
	if (x_diff > sumOfRadii)
		return;
	float y_diff = position[ID1].y - position[ID2].y;
	if (y_diff > sumOfRadii)
		return;
	float z_diff = position[ID1].z - position[ID2].z;
	if (z_diff > sumOfRadii)
		return;
	auto distance = glm::length(glm::vec3(x_diff, y_diff, z_diff));
	auto difference = distance - sumOfRadii;
	if (difference < 0)
	{
		auto normal = glm::normalize(position[ID2] - position[ID1]);
		position[ID2] -= (0.5f * difference * normal);
		position[ID1] += (0.5f * difference * glm::normalize(normal));

		// Calculate momentum conservation
		glm::vec3 relativeVelocity = velocity[ID1] - velocity[ID2]; // Relative velocity of the objects
		float collisionSpeed = glm::dot(relativeVelocity, normal); // Collision speed along the normal direction
		float elasticity = (restitution[ID2] + restitution[ID2]) / 2;
		glm::vec3 normalImpulse = -(1 + elasticity) * normal * collisionSpeed / (mass[ID1] + mass[ID2]); // Calculate impulse using masses, relative velocity, and coefficient of restitution
		velocity[ID1] += normalImpulse * mass[ID2]; // Update velocity of object 1
		velocity[ID2] -= normalImpulse * mass[ID1]; // Update velocity of object 2
	}
}

void BallManager::resolveCollisions_fixed_buckets()
{
	//split indexes into buckets based on x position
	std::vector<int> Bucket1;
	std::vector<int> Bucket2;
	std::vector<int> Bucket3;
	std::vector<int> Bucket4;
	//add element for assigning pointer
	Bucket1.push_back(0);
	Bucket2.push_back(0);
	Bucket3.push_back(0);
	Bucket4.push_back(0);

	for (int i = 0; i < count; i++)
	{
		if (position[i].x < (- boundarySize / 2) + maxWidth)
			Bucket1.push_back(i);
		if (position[i].x > (-boundarySize / 2) && position[i].x < maxWidth)
			Bucket2.push_back(i);
		if (position[i].x > 0 && position[i].x < (boundarySize / 2) + maxWidth)
			Bucket3.push_back(i);
		if (position[i].x > boundarySize/2)
			Bucket4.push_back(i);
	}

	int* buckets[] = {&Bucket1[0], &Bucket2[0], &Bucket3[0] , &Bucket4[0] };
	int bucketSize[] = {Bucket1.size(), Bucket2.size(), Bucket3.size(), Bucket4.size()};


	::concurrency::parallel_for(size_t(0), (size_t)4, [&](size_t B)
	{
		int* bucket = buckets[B];

		if (bucketSize[B] > 1)
		{
			::concurrency::parallel_for(size_t(1), (size_t)(bucketSize[B] - 1), [&](size_t i)
			{
				int ID1 = bucket[i];

				for (int j = i + 1; j < bucketSize[B]; j++)
				{
					int ID2 = bucket[j];

					resolveCollision(ID1, ID2);

				}

			});
		}
	});
	
}

void BallManager::resolveCollisions_dynamic_buckets()
{
	//fill array with ID's
	std::vector<int> all_balls(count);
	std::iota(all_balls.begin(), all_balls.end(), 0);
	// Call the recursive function on all the balls
	resolveCollisionsRecursive(&all_balls[0], count, glm::vec2(-boundarySize, boundarySize));
}

void BallManager::resolveCollisionsRecursive(int* bucket, int size, const glm::vec2& x_range)
{
	if (size < max_bucket_size || x_range.y - x_range.x < 2 * maxWidth)
	{
		::concurrency::parallel_for(size_t(1), (size_t)(size - 1), [&](size_t i)
		{
			int ID1 = bucket[i];

			for (int j = i + 1; j < size; j++)
			{
				int ID2 = bucket[j];

				resolveCollision(ID1, ID2);

			}
		});
	}
	else
	{
		float midpoint = (x_range.x + x_range.y) / 2;
		std::vector<int> left_bucket;
		std::vector<int> right_bucket;
		for (int i = 0; i < size; i++)
		{
			//allow balls to enter both buckets to check edge case
			if (position[i].x < midpoint)
				left_bucket.push_back(i);
			//if (position[i].x > midpoint - 0.5 * maxWidth)
			else
				right_bucket.push_back(i);
		}
		resolveCollisionsRecursive(&left_bucket[0], left_bucket.size(), glm::vec2(x_range.x, midpoint));
		resolveCollisionsRecursive(&right_bucket[0], right_bucket.size(), glm::vec2(midpoint, x_range.y));
	}
}


void BallManager::update(float deltaTime)
{
	time += deltaTime;
	updatePositions(deltaTime);
	//resolveCollisions_dynamic_buckets();
	resolveCollisions_fixed_buckets();
	//resolveCollisions_no_buckets();
}



