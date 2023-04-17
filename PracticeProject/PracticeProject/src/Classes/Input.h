#pragma once
#include <queue>
#include "Camera.h"
#include<iostream>
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
    const float cameraSpeed = 50.0f;
    const float mouseSensitivity = 0.1f;
    const float scrollSensitivity = 10.0f;
    float scrollOffset = 0;
    float previousMouseX = 0;
    float mouseX = 0;
    float previousMouseY = 0;
    float mouseY = 0;
    bool firstMouse = true;
    int coolDown = 0;

    ::std::queue<int> input;
    std::vector<InputObserver*> observers;

    void ProcessInput(float deltaTime)
    {
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
};
