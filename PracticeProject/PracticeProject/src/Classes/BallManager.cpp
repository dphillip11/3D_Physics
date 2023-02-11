#include "BallManager.h"
#include "../Libraries/glm/glm/gtc/matrix_transform.hpp"
#include <ppl.h>
#include "../Libraries/glm/glm/geometric.hpp"



void BallManager::resolveCollisions()
{
	//split indexes into buckets based on x position
	std::vector<int> buckets[2];
	for (int i = 0; i < ballCount; i++)
		{
			if (position[i].x < (2 * maxRadius))
				buckets[0].push_back(i);
			if (position[i].x > (-2 * maxRadius))
				buckets[1].push_back(i);
		}
	//run each bucket concurrently
	::concurrency::parallel_for(size_t(0), (size_t)2, [&](size_t b)
		{
			//run each element concurrently
			::concurrency::parallel_for(size_t(0), (size_t)sizeof(buckets[b]), [&](size_t i)
			//for (int i = 0; i < ballCount; i++)
				{
					for (int j = i + 1; j < sizeof(buckets[b]); j++)
					{
						float sumOfRadii = radius[buckets[b][i]] + radius[buckets[b][j]];
						float x_diff = position[buckets[b][i]].x - position[buckets[b][j]].x;
						if (x_diff > sumOfRadii)
							continue;
						float y_diff = position[buckets[b][i]].y - position[buckets[b][j]].y;
						if (y_diff > sumOfRadii)
							continue;
						float z_diff = position[buckets[b][i]].z - position[buckets[b][j]].z;
						if (z_diff > sumOfRadii)
							continue;
						auto distance = glm::length(glm::vec3(x_diff, y_diff, z_diff));
						auto difference = distance - sumOfRadii;
						if (difference < 0)
						{
							auto normal = glm::normalize(position[buckets[b][j]] - position[buckets[b][i]]);
							position[buckets[b][j]] -= (0.5f * difference * normal);
							position[i] += (0.5f * difference * glm::normalize(normal));
							auto relativeVelocity = velocity[buckets[b][i]] - velocity[buckets[b][j]];
							float collisionSpeed = glm::dot(relativeVelocity, normal);
							if (collisionSpeed > 0)
							{
								glm::vec3 impulse = normal * collisionSpeed;
								velocity[buckets[b][i]] -= impulse;
								velocity[buckets[b][j]] += impulse;
							}
						}
					}
				}
	);
		}
	);

	
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
}

void BallManager::spawnBalls(int n)
{
	for (int i = 0; i < n; i++)
	{
		//testing/////
		/*int x = i % 2 == 0 ? 1 : -1;
		position.push_back(glm::vec3(x*5,0,0));
		velocity.push_back(glm::vec3(-x, 0, 0));
		radius.push_back(1);*/
		/////////////

		position.push_back(randomVec3(boundarySize));
		velocity.push_back(randomVec3(maxSpeed));
		radius.push_back(randomVal(maxRadius, true));
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