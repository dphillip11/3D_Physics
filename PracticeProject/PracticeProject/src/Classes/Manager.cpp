#include "Manager.h"
#include <glm/glm/gtc/matrix_transform.hpp>



float Manager::randomVal(float magnitude, bool onlyPositive)
{
	//create a random number of a given magnitude with 2 decimal places
	float value = (rand() % ((int)(200 * magnitude) / 100)) - magnitude;
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
		velocity[i].y -= deltaTime * gravity;
		position[i] += (velocity[i] * deltaTime);

		if (abs(position[i].x) > boundarySize - halfWidth[i])
		{
			int sign = position[i].x > 0 ? 1 : -1;
			position[i].x = sign * (boundarySize - halfWidth[i]);
			velocity[i].x *= -restitution[i];
		}
		if (abs(position[i].y) > boundarySize - halfWidth[i])
		{
			int sign = position[i].y > 0 ? 1 : -1;
			position[i].y = sign * (boundarySize - halfWidth[i]);
			velocity[i].y *= -restitution[i];
		}
		if (abs(position[i].z) > boundarySize - halfWidth[i])
		{
			int sign = position[i].z > 0 ? 1 : -1;
			position[i].z = sign * (boundarySize - halfWidth[i]);
			velocity[i].z *= -restitution[i];
		}

	}

}

void Manager::spawnObject(glm::vec3 new_position, glm::vec3 new_velocity, float new_radius)
{
	position.push_back(new_position);
	velocity.push_back(new_velocity);
	halfWidth.push_back(new_radius);
	mass.push_back(pow(new_radius, 3));
	restitution.push_back(0.3 + randomVal(0.5, true));
	count++;
}

void Manager::spawnObjects(int n)
{
	for (int i = 0; i < n; i++)
	{
		position.push_back(randomVec3(boundarySize));
		velocity.push_back(randomVec3(maxSpeed));
		halfWidth.push_back(randomVal(maxWidth / 2, true));
		mass.push_back(pow(halfWidth[i],3));
		restitution.push_back(0.3 + randomVal(0.5, true));
		count++;
	}
}

void Manager::spawnCoplanarObjects(int n)
{
	for (int i = 0; i < n; i++)
	{
		position.push_back(glm::vec3(randomVal(boundarySize), 0, randomVal(boundarySize)));
		velocity.push_back(glm::vec3(randomVal(maxSpeed), 0, randomVal(maxSpeed)));
		halfWidth.push_back(randomVal(maxWidth / 2, true));
		mass.push_back(pow(halfWidth[i], 3));
		restitution.push_back(0.3 + randomVal(0.5, true));
		count++;
	}
}

void Manager::populateColors(int n)
{
	for (int i = 0; i < n; i++)
	{
		glm::vec3 color;
		color.r = (randomVal(255, true))/255;
		color.g = (randomVal(255, true))/255;
		color.b = (randomVal(255, true))/255;
		colors.push_back(color);
	}

}

void Manager::drawObjects(Camera camera)
{
	//setup shader
	object->shader->use();
	glm::mat4 VP = camera.projection * camera.lookAt();
	for (int i = 0; i < count; i++)
	{
		glm::mat4 model = glm::translate(glm::mat4(1), position[i]);
		model = glm::scale(model, glm::vec3(halfWidth[i], halfWidth[i], halfWidth[i]));
		object->shader->setMat4("MVP", VP * model);
		object->shader->setMat4("model", model);
		object->shader->setVec3("color", colors[i % colors.size()]);
		object->shader->setInt("shininess", (i % 50) + 1);
		object->shader->setVec3("objectPos", position[i]);
		object->shader->setVec3("viewPos", camera._position);
		object->draw();
	}
}