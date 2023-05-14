#pragma once

#include "Camera.h"
#include "InputObserver.h"


enum KEYS {
	UP,
	DOWN,
	LEFT,
	RIGHT,
	W,
	A,
	S,
	D,
	SPACE
};

class Input {
public:
	const float mouseSensitivity = 0.1f;
	const float scrollSensitivity = 10.0f;
	float scrollOffset = 0;
	float previousMouseX = 0;
	float mouseX = 0;
	float previousMouseY = 0;
	float mouseY = 0;
	bool firstMouse = true;
	float time = 0;
	float coolDownInterval = 1.0f;
	//track time of key press;
	std::map<int, float> keyCoolDown;
	std::map<int, bool> coolDownKeys;
	::std::queue<int> input;
	std::vector<InputObserver*> observers;

	Input();

	void LogKey(int key);

	void ProcessInput(float deltaTime);

};
