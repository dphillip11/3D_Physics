#include "pch.h"
#include "Input.h"

Input::Input()
{
	coolDownKeys[KEYS::SPACE] = true;
}

void Input::LogKey(int key)
{
	//check if the key is on the cooldown list
	if (!coolDownKeys[key])
		input.push(key);
	else
	{
		float keyPressTime = keyCoolDown[key];
		if (!keyPressTime || time - keyPressTime > coolDownInterval)
		{
			input.push(key);
			keyCoolDown[key] = time;
		}
	}

}

void Input::ProcessInput(float deltaTime)
{
	time = time + deltaTime;
	if (scrollOffset != 0)
	{
		for (auto observer : observers)
		{
			observer->onMouseScroll(scrollOffset * scrollSensitivity, deltaTime);
		}
		scrollOffset = 0;
	}

	if (firstMouse)
	{
		previousMouseX = mouseX;
		previousMouseY = mouseY;
		firstMouse = false;
	}
	else
	{
		float mouseDX = mouseSensitivity * (mouseX - previousMouseX);
		previousMouseX = mouseX;
		float mouseDY = mouseSensitivity * (mouseY - previousMouseY);
		previousMouseY = mouseY;
		for (auto observer : observers)
		{
			observer->onMouseMove(mouseDX, mouseDY, deltaTime);
		}
	}
	while (!input.empty())
	{
		for (auto observer : observers)
		{
			observer->onKeyPress(input.front(), deltaTime);
		}
		input.pop();
	}

}