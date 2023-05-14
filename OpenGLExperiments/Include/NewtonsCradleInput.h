#pragma once
#pragma once
#include "InputObserver.h"
#include "rayTracing.h"


class NewtonsCradleInput : public InputObserver
{
private:
    rayTracing* _rt = nullptr;
    glm::vec3 mousePos{ 0,0,0 };
    float camDepth = 0.5;
    float camHeight = 8;
    glm::vec3 camPos{ 0,5,-10 };

public:
    NewtonsCradleInput(rayTracing* rt) : _rt(rt) {};
    void onKeyPress(int key, float deltaTime);
    void onMouseScroll(float scroll_value, float deltaTime);
    void onMousePress(float deltaTime);
    void onMouseMove(float dx, float dy, float deltaTime);
    void processInput();
};