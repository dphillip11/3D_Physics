#include "BallManager.h"
#include <glm/glm/gtc/matrix_transform.hpp>

void BallManager::updatePositions(float deltaTime)
{
	//TODO: run these is parallel, SIMD etc.
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