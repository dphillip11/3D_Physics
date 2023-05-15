#pragma once
#include "PCH/pch.h"
#include "BasicCameraInput.h"
#include "Input.h"




void BasicCameraInput::onKeyPress(int key, float deltaTime)
{
	if (key == KEYS::SPACE)
	{
		camera->isLockedOn = !camera->isLockedOn;
	}
	if (key == KEYS::A)
	{
	}
	else if (key == KEYS::UP)
		camera->moveForward(deltaTime * panSpeed);
	else if (key == KEYS::DOWN)
		camera->moveForward(-deltaTime * panSpeed);
	else if (key == KEYS::RIGHT)
		camera->moveRight(deltaTime * panSpeed);
	else if (key == KEYS::LEFT)
		camera->moveRight(-deltaTime * panSpeed);
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
	camera->rotate(dx * deltaTime * rotateSpeed, dy * deltaTime * rotateSpeed);
}