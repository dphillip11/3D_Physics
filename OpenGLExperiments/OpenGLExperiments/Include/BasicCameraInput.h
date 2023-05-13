#pragma once
#include "BasicCameraInput.h"
#include "Camera.h"
#include "InputObserver.h"


class BasicCameraInput : public InputObserver
{
public:
	float panSpeed = 0.1;
	float rotateSpeed = 100;

	Camera* camera;
	BasicCameraInput(Camera* new_camera) : camera(new_camera) {};
	void onKeyPress(int key, float deltaTime);
	void onMouseScroll(float scroll_value, float deltaTime);
	void onMousePress(float deltaTime);
	void onMouseMove(float dx, float dy, float deltaTime);
};

