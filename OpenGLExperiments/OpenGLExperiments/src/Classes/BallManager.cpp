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


void BallManager::resolveCollisions_dynamic_buckets()
{
	//fill array with ID's
	std::vector<int> all_balls(count);
	std::iota(all_balls.begin(), all_balls.end(), 0);
	// Call the recursive function on all the balls
	int bucket_count = 0;
	glm::vec2 boundary = glm::vec2(-boundarySize, boundarySize);
	resolveCollisionsRecursive(&all_balls[0], count, boundary, boundary, boundary, bucket_count);
}

void BallManager::resolveCollisionsRecursive(int* bucket, int size, const glm::vec2& x_range, const glm::vec2& z_range, const glm::vec2& y_range, int &bucket_count)
{
	bucket_count++;
	if (size < max_bucket_size || x_range.y - x_range.x < 2 * maxWidth)
	{
		::concurrency::parallel_for(size_t(0), (size_t)(size - 1), [&](size_t i)
		{
		//for (int i = 0; i < size - 1; i++)
		{
			int ID1 = bucket[i];

			for (int j = i + 1; j < size; j++)
			{
				int ID2 = bucket[j];

				resolveCollision(ID1, ID2);

			}
		}
		});
	}
	else
	{
		bucket_count--;
		float midpoint_x = (x_range.x + x_range.y) / 2;
		float midpoint_y = (y_range.x + y_range.y) / 2;
		float midpoint_z = (z_range.x + z_range.y) / 2;
		//lower y portion
		std::vector<int> Q1_bucket;
		std::vector<int> Q2_bucket;
		std::vector<int> Q3_bucket;
		std::vector<int> Q4_bucket;
		//upper y portion
		std::vector<int> Q5_bucket;
		std::vector<int> Q6_bucket;
		std::vector<int> Q7_bucket;
		std::vector<int> Q8_bucket;

		float offset = maxWidth / 2;

		for (int i = 0; i < size; i++)
		{
			int ID = bucket[i];
			//allow balls to enter multiple buckets to check edge cases
		
			if (position[ID].y < midpoint_y + offset)
			{
				if (position[ID].x < midpoint_x + offset && position[ID].z < midpoint_z + offset)
					Q1_bucket.push_back(ID);
				if (position[ID].x < midpoint_x + offset && position[ID].z > midpoint_z - offset)
					Q2_bucket.push_back(ID);
				if (position[ID].x > midpoint_x - offset && position[ID].z < midpoint_z + offset)
					Q3_bucket.push_back(ID);
				if (position[ID].x > midpoint_x - offset && position[ID].z > midpoint_z - offset)
					Q4_bucket.push_back(ID);
			}
			if (position[ID].y > midpoint_y - offset)
			{
				if (position[ID].x < midpoint_x + offset && position[ID].z < midpoint_z + offset)
					Q5_bucket.push_back(ID);
				if (position[ID].x < midpoint_x + offset && position[ID].z > midpoint_z - offset)
					Q6_bucket.push_back(ID);
				if (position[ID].x > midpoint_x - offset && position[ID].z < midpoint_z + offset)
					Q7_bucket.push_back(ID);
				if (position[ID].x > midpoint_x - offset && position[ID].z > midpoint_z - offset)
					Q8_bucket.push_back(ID);
			}
		}

		if (Q1_bucket.size()>0)
			resolveCollisionsRecursive(&Q1_bucket[0], Q1_bucket.size(), glm::vec2(x_range.x, midpoint_x + offset), glm::vec2(y_range.x, midpoint_y + offset), glm::vec2(z_range.x, midpoint_z + offset), bucket_count);
		if (Q2_bucket.size() > 0)
			resolveCollisionsRecursive(&Q2_bucket[0], Q2_bucket.size(), glm::vec2(x_range.x, midpoint_x + offset), glm::vec2(y_range.x, midpoint_y + offset), glm::vec2(midpoint_z - offset, z_range.y), bucket_count);
		if (Q3_bucket.size() > 0)
			resolveCollisionsRecursive(&Q3_bucket[0], Q3_bucket.size(), glm::vec2(midpoint_x - offset, x_range.y), glm::vec2(y_range.x, midpoint_y + offset), glm::vec2(z_range.x, midpoint_z + offset), bucket_count);
		if (Q4_bucket.size() > 0)
			resolveCollisionsRecursive(&Q4_bucket[0], Q4_bucket.size(), glm::vec2(midpoint_x - offset, x_range.y), glm::vec2(y_range.x, midpoint_y + offset), glm::vec2(midpoint_z, z_range.y), bucket_count);
		if (Q5_bucket.size() > 0)
			resolveCollisionsRecursive(&Q5_bucket[0], Q5_bucket.size(), glm::vec2(x_range.x, midpoint_x + offset), glm::vec2(midpoint_y - offset, y_range.y), glm::vec2(z_range.x, midpoint_z + offset), bucket_count);
		if (Q6_bucket.size() > 0)
			resolveCollisionsRecursive(&Q6_bucket[0], Q6_bucket.size(), glm::vec2(x_range.x, midpoint_x + offset), glm::vec2(midpoint_y - offset, y_range.y), glm::vec2(midpoint_z - offset, z_range.y), bucket_count);
		if (Q7_bucket.size() > 0)
			resolveCollisionsRecursive(&Q7_bucket[0], Q7_bucket.size(), glm::vec2(midpoint_x - offset, x_range.y), glm::vec2(midpoint_y - offset, y_range.y), glm::vec2(z_range.x, midpoint_z + offset), bucket_count);
		if (Q8_bucket.size() > 0)
			resolveCollisionsRecursive(&Q8_bucket[0], Q8_bucket.size(), glm::vec2(midpoint_x - offset, x_range.y), glm::vec2(midpoint_y - offset, y_range.y), glm::vec2(midpoint_z, z_range.y), bucket_count);
	}
}


void BallManager::update(float deltaTime)
{
	time += deltaTime;
	//this reduces jitter and doesn't hurt performance as much as you might imagine
	for (int i = 0; i < collision_cycles; i++)
	{
		updatePositions(deltaTime / collision_cycles);
		resolveCollisions_dynamic_buckets();
	}
}



