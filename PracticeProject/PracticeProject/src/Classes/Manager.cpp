#include "Manager.h"


float Manager::randomVal(float magnitude, bool onlyPositive)
{
	//create a random number of a given magnitude with 2 decimal places
	float value = ((rand() % (int)(200 * magnitude)) / 100 - magnitude);
	if (onlyPositive)
		return abs(value);
	else
		return value;
}

glm::vec3 Manager::randomVec3(float magnitude)
{
	return glm::vec3(randomVal(magnitude), randomVal(magnitude), randomVal(magnitude));
}

void Manager::updatePositions(float deltaTime)
{
	for (int i = 0; i < count; i++)
	{
		position[i] += (velocity[i] * deltaTime);
	}

	for (int i = 0; i < count; i++)
	{
		if (abs(position[i].x) > boundarySize - halfWidth[i])
		{
			position[i].x -= (velocity[i].x * deltaTime);
			velocity[i].x *= -1;
		}
		if (abs(position[i].y) > boundarySize - halfWidth[i])
		{
			position[i].y -= (velocity[i].y * deltaTime);
			velocity[i].y *= -1;
		}
		if (abs(position[i].z) > boundarySize - halfWidth[i])
		{
			position[i].z -= (velocity[i].z * deltaTime);
			velocity[i].z *= -1;
		}
	}

}