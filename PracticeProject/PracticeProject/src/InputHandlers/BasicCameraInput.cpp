#include "BasicCameraInput.h"
#pragma once
#include "../Classes/Input.h"

void BasicCameraInput::onKeyPress(int key, float deltaTime)
{
	if (key == KEYS::SPACE)
	{
		camera->isLockedOn = !camera->isLockedOn;
	}
	else if (key == KEYS::UP)
		camera->moveForward(deltaTime);
	else if (key == KEYS::DOWN)
		camera->moveForward(-deltaTime);
	else if (key == KEYS::RIGHT)
		camera->moveRight(deltaTime);
	else if (key == KEYS::LEFT)
		camera->moveRight(-deltaTime);
}

void BasicCameraInput::onMouseScroll(float scroll_value, float deltaTime)
{
	camera->zoom(scroll_value * deltaTime);
}

void BasicCameraInput::onMousePress(float deltaTime)
{

}

void BasicCameraInput::onMouseMove(float dx, float dy, float deltaTime)
{
	camera->rotate(dx * deltaTime, dy * deltaTime);
}