#include "BallManager.h"
#include <glm/glm/gtc/matrix_transform.hpp>
#include <ppl.h>
#include <glm/glm/geometric.hpp>

void BallManager::resolveCollisions_no_buckets()
{
		for (int i = 0; i < ballCount; i++)
		{
			for (int j = i + 1; j < ballCount; j++)
			{
				float sumOfRadii = radius[i] + radius[j];
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

	Bucket1.push_back(0);
	Bucket2.push_back(0);
	Bucket3.push_back(0);
	Bucket4.push_back(0);

	for (int i = 0; i < ballCount; i++)
	{
		if (position[i].x < (- boundarySize / 2) + 2 * maxRadius)
			Bucket1.push_back(i);
		if (position[i].x > (-boundarySize / 2) && position[i].x < 2 * maxRadius)
			Bucket2.push_back(i);
		if (position[i].x > 0 && position[i].x < 2 * maxRadius + 2 * maxRadius)
			Bucket3.push_back(i);
		if (position[i].x > boundarySize/2)
			Bucket4.push_back(i);
	}

	int* buckets[] = {&Bucket1[0], &Bucket2[0], &Bucket3[0] , &Bucket4[0] };
	int bucketSize[] = {Bucket1.size(), Bucket2.size(), Bucket3.size(), Bucket4.size()};

	//for (int B = 0; B < 4; B++)
	::concurrency::parallel_for(size_t(0), (size_t)4, [&](size_t B)
		{
			int* bucket = buckets[B];

			if (bucketSize[B] > 1)
			{
				//for (int i = 0; i < bucketSize[B] - 1; i++)
				::concurrency::parallel_for(size_t(0), (size_t)(bucketSize[B] - 1), [&](size_t i)
					{
						int ID1 = bucket[i];

				for (int j = i + 1; j < bucketSize[B]; j++)
				{
					int ID2 = bucket[j];

					float sumOfRadii = radius[bucket[i]] + radius[bucket[j]];
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
						auto relativeVelocity = velocity[bucket[i]] - velocity[bucket[j]];
						float collisionSpeed = glm::dot(relativeVelocity, normal);
						if (collisionSpeed > 0)
						{
							glm::vec3 impulse = normal * collisionSpeed;
							velocity[bucket[i]] -= impulse;
							velocity[bucket[j]] += impulse;
						}
					}


				}

					});
			}
		});


	
}


void BallManager::updatePositions(float deltaTime)
{
		for (int i = 0; i < ballCount; i++)
		{
			position[i] += (velocity[i] * deltaTime);
		}

		for (int i = 0; i < ballCount; i++)
		{
			if (abs(position[i].x) > boundarySize - radius[i])
			{
				position[i].x -= (velocity[i].x * deltaTime);
				velocity[i].x *= -1;
			}
			if (abs(position[i].y) > boundarySize - radius[i])
			{
				position[i].y -= (velocity[i].y * deltaTime);
				velocity[i].y *= -1;
			}
			if (abs(position[i].z) > boundarySize - radius[i])
			{
				position[i].z -= (velocity[i].z * deltaTime);
				velocity[i].z *= -1;
			}
		}
		resolveCollisions();
		//resolveCollisions_no_buckets();
}

void BallManager::spawnBalls(int n)
{
	for (int i = 0; i < n; i++)
	{
		position.push_back(randomVec3(boundarySize));
		velocity.push_back(randomVec3(maxSpeed));
		radius.push_back(randomVal(maxRadius, true));
		ballCount++;
	}
}

void BallManager::spawnOpposingBalls()
{
	for (int i = 0; i < 8; i++)
	{
		int x = i == 0 ? 1 : -1;
		position.push_back(glm::vec3(x*5,0,i*x));
		velocity.push_back(glm::vec3(-x * (i+1), 0, 0));
		radius.push_back(1);
		ballCount++;
	}
}

void BallManager::drawBalls(glm::mat4 view, glm::mat4 projection) 
{
	//setup shader
	ball->sphereShader->use();

	for (int i = 0; i < ballCount; i++)
	{	
		glm::mat4 model = glm::translate(glm::mat4(1), position[i]);
		model = glm::scale(model, glm::vec3(radius[i], radius[i], radius[i]));
		ball->sphereShader->setMat4("MVP", projection * view * model);
		ball->draw();
	}
	
}

float BallManager::randomVal(float magnitude, bool onlyPositive)
{
	//create a random number of a given magnitude with 2 decimal places
	float value = ((rand() % (int)(200 * magnitude)) / 100 - magnitude);
	if (onlyPositive)
		return abs(value);
	else
		return value;
}

glm::vec3 BallManager::randomVec3(float magnitude)
{
	return glm::vec3(randomVal(magnitude), randomVal(magnitude), randomVal(magnitude));
}