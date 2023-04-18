#include "BallManager.h"
#include <glm/glm/gtc/matrix_transform.hpp>
#include <ppl.h>
#include <glm/glm/geometric.hpp>

void BallManager::resolveCollisions_no_buckets()
{
		for (int i = 0; i < count; i++)
		{
			for (int j = i + 1; j < count; j++)
			{
				float sumOfRadii = halfWidth[i] + halfWidth[j];
				float x_diff = position[i].x - position[j].x;
				if (x_diff > sumOfRadii)
					continue;
				float y_diff = position[i].y - position[j].y;
				if (y_diff > sumOfRadii)
					continue;
				float z_diff = position[i].z - position[j].z;
				if (z_diff > sumOfRadii)
					continue;
				auto distance = glm::length(glm::vec3(x_diff, y_diff, z_diff));
				auto difference = distance - sumOfRadii;
				if (difference < 0)
				{
					auto normal = glm::normalize(position[j] - position[i]);
					position[j] -= (0.5f * difference * normal);
					position[i] += (0.5f * difference * glm::normalize(normal));
					auto relativeVelocity = velocity[i] - velocity[j];
					float collisionSpeed = glm::dot(relativeVelocity, normal);
					if (collisionSpeed > 0)
					{
						glm::vec3 impulse = normal * collisionSpeed;
						velocity[i] -= impulse;
						velocity[j] += impulse;
					}
				}
			}
		}
}

void BallManager::resolveCollisions()
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

					float sumOfRadii = halfWidth[bucket[i]] + halfWidth[bucket[j]];
					float x_diff = position[bucket[i]].x - position[bucket[j]].x;
					if (x_diff > sumOfRadii)
						continue;
					float y_diff = position[bucket[i]].y - position[bucket[j]].y;
					if (y_diff > sumOfRadii)
						continue;
					float z_diff = position[bucket[i]].z - position[bucket[j]].z;
					if (z_diff > sumOfRadii)
						continue;
					auto distance = glm::length(glm::vec3(x_diff, y_diff, z_diff));
					auto difference = distance - sumOfRadii;
					if (difference < 0)
					{
						auto normal = glm::normalize(position[bucket[j]] - position[bucket[i]]);
						position[bucket[j]] -= (0.5f * difference * normal);
						position[bucket[i]] += (0.5f * difference * glm::normalize(normal));

						// Calculate momentum conservation
						float m1 = mass[bucket[i]];
						float m2 = mass[bucket[j]];
						glm::vec3 relativeVelocity = velocity[bucket[i]] - velocity[bucket[j]]; // Relative velocity of the objects
						float collisionSpeed = glm::dot(relativeVelocity, normal); // Collision speed along the normal direction
						float elasticity = (restitution[bucket[j]] + restitution[bucket[j]]) / 2;
						glm::vec3 normalImpulse = -(1 + elasticity) * normal * collisionSpeed / (m1 + m2); // Calculate impulse using masses, relative velocity, and coefficient of restitution
						velocity[bucket[i]] += normalImpulse * m2; // Update velocity of object 1
						velocity[bucket[j]] -= normalImpulse * m1; // Update velocity of object 2
					}


				}

					});
			}
		});


	
}

void BallManager::update(float deltaTime)
{
	time += deltaTime;
	if (isCoolingDown && time - coolDownTime > coolDownInterval)
		isCoolingDown = false;
	updatePositions(deltaTime);
	resolveCollisions();
	//resolveCollisions_no_buckets();
}



