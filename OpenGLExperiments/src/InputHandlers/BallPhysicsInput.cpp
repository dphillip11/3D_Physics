#pragma once
#include "PCH/pch.h"
#include "BallPhysicsInput.h"
#include "Input.h"

void BallPhysicsInput::onKeyPress(int key, float deltaTime)
{
	if (key == KEYS::SPACE)
	{
		BM->spawnObject(glm::vec3(0, BM->boundarySize - BM->maxWidth, 0), glm::vec3(0, rand() % 500 - 1000, 0), BM->maxWidth / 2);
		BM->mass[BM->count - 1] = 100.0f * BM->mass[BM->count - 1];
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
	camera->zoom(scroll_value * deltaTime);
}

void BallPhysicsInput::onMousePress(float deltaTime)
{

}

void BallPhysicsInput::onMouseMove(float dx, float dy, float deltaTime)
{
	camera->rotate(dx * deltaTime, dy * deltaTime);
}