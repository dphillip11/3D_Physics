#include "PCH/pch.h"
#include "Manager.h"
#include "Ball.h"



float Manager::randomVal(float magnitude, bool onlyPositive)
{
	//create a random number of a given magnitude with 2 decimal places
	float value = (rand() % (int)(200 * magnitude)) / 100 - magnitude;
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
		velocity[i].y -= (deltaTime * gravity);
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
	mass.push_back(pow(new_radius, 3.0f));
	restitution.push_back(min_restitution + randomVal(max_restitution - min_restitution, true));
	count++;
}

void Manager::spawnObjects(int n)
{
	for (int i = 0; i < n; i++)
	{
		position.push_back(randomVec3(boundarySize));
		velocity.push_back(randomVec3(maxSpeed));
		halfWidth.push_back(randomVal(maxWidth / 2, true));
		mass.push_back(pow(halfWidth[i], 3.0f));
		restitution.push_back(min_restitution + randomVal(max_restitution - min_restitution, true));
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
		mass.push_back(pow(halfWidth[i], 3.0f));
		restitution.push_back(min_restitution + randomVal(max_restitution - min_restitution, true));
		count++;
	}
}

void Manager::generateBuffers()
{
	glGenBuffers(1, &VBO_pos);
	object->setVertices(&position[0], (int)position.size() * 3, object->_VAO, VBO_pos);
	object->setAttributes(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));
	glVertexAttribDivisor(1, 1);
	glGenBuffers(1, &VBO_radius);
	object->setVertices(&halfWidth[0], (int)halfWidth.size(), object->_VAO, VBO_radius);
	object->setAttributes(2, 1, GL_FLOAT, GL_FALSE, sizeof(float), (void*)(0));
	glVertexAttribDivisor(2, 1);
}

void Manager::drawObjects(Camera camera)
{
	object->shader->use();
	glm::mat4 VP = camera.projection * camera.lookAt();
	object->shader->setMat4("VP", VP);
	object->shader->setVec3("viewPos", camera._position);
	glBindVertexArray(object->_VAO);
	object->setVertices(&position[0], (int)position.size() * 3, object->_VAO, VBO_pos);
	object->setVertices(&halfWidth[0], (int)halfWidth.size(), object->_VAO, VBO_radius);
	glDrawElementsInstanced(GL_TRIANGLES, object->indexCount, GL_UNSIGNED_INT, 0, count);
}