#pragma once
#include <queue>
#include "Camera.h"
#include<iostream>
#include "InputObserver.h"
#include <map>

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

    Input()
    {
        coolDownKeys[KEYS::SPACE] = true;
    }

    void LogKey(int key)
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

    void ProcessInput(float deltaTime)
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
};
