#pragma once
#include "BasicCameraInput.h"
#include "../Classes/Camera.h"
#include "../Classes/InputObserver.h"


class BasicCameraInput : public InputObserver
{
public:
    Camera* camera;
    BasicCameraInput(Camera* new_camera) : camera(new_camera) {};
    void onKeyPress(int key, float deltaTime);
    void onMouseScroll(float scroll_value, float deltaTime);
    void onMousePress(float deltaTime);
    void onMouseMove(float dx, float dy, float deltaTime);
};

