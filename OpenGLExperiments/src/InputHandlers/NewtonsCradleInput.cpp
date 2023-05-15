#include "PCH/pch.h"
#include "NewtonsCradleInput.h"
#include "Input.h"


void NewtonsCradleInput::onKeyPress(int key, float deltaTime)
{
	if (key == KEYS::UP)
	{
		camHeight += 5 * deltaTime;
		camHeight = (float)fmin(fmax(0.1f, camHeight), 30);
	}
	else if (key == KEYS::DOWN)
	{
		camHeight -= 5 * deltaTime;
		camHeight = (float)fmin(fmax(0.1f, camHeight), 30);
	}
	if (key == KEYS::LEFT)
	{
		mousePos += glm::vec3(50 * deltaTime, 0, 0);
	}
	else if (key == KEYS::RIGHT)
	{
		mousePos -= glm::vec3(50 * deltaTime, 0, 0);
	}

}

void NewtonsCradleInput::onMouseScroll(float scroll_value, float deltaTime)
{
	camDepth = (float)fmin(10.0, fmax(camDepth - scroll_value * deltaTime, 0.3));
}

void NewtonsCradleInput::onMousePress(float deltaTime)
{

}

void NewtonsCradleInput::onMouseMove(float dx, float dy, float deltaTime)
{

}

void NewtonsCradleInput::processInput()
{
	_rt->shader->setVec3("iMouse", mousePos);
	_rt->shader->setFloat("cam_depth", camDepth);
	_rt->shader->setFloat("cam_y", camHeight);
}

