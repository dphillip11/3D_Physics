#include "BallPhysicsInput.h"
#pragma once
#include "../Classes/Input.h"

void BallPhysicsInput::onKeyPress(int key, float deltaTime)
{
	if (BM && key == KEYS::SPACE && !BM->isCoolingDown)
	{
		BM->spawnObject(glm::vec3(0, BM->boundarySize - 20, 0), glm::vec3(0, -100, 0), 20);
		BM->isCoolingDown = true;
		BM->coolDownTime = BM->time;
	}
	else if (key == KEYS::UP)
		camera->moveForward(50 * deltaTime);
	else if (key == KEYS::DOWN)
		camera->moveForward(-50 * deltaTime);
	else if (key == KEYS::RIGHT)
		camera->moveRight(50 * deltaTime);
	else if (key == KEYS::LEFT)
		camera->moveRight(-50 * deltaTime);
}

void BallPhysicsInput::onMouseScroll(float scroll_value, float deltaTime)
{
	camera->zoom(scroll_value * zoomSpeed * deltaTime);
}

void BallPhysicsInput::onMousePress(float deltaTime)
{

}

void BallPhysicsInput::onMouseMove(float dx, float dy, float deltaTime)
{
	camera->rotate(panSpeed * dx * deltaTime, panSpeed * dy * deltaTime);
}