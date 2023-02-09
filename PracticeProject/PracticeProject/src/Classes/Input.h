#pragma once
#include <queue>
#include "Camera.h"


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
    float pitch = 0;
    float yaw = -90;
    float previousMouseX = 0;
    float mouseX = 0;
    float previousMouseY = 0;
    float mouseY = 0;
    bool firstMouse = true;
    ::std::queue<int> input;

    void ProcessInput(float deltaTime, Camera& camera)
    {
        const float cameraSpeed = 0.05f;
        const float mouseSensitivity = 0.1f;
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
            camera.rotate(mouseDX, mouseDY);
        }
        while (!input.empty())
        {
            //up
            if (input.front() == KEYS::UP)
            {
                camera.moveForward(deltaTime * 5);
                input.pop();
            }
            //down
            else if (input.front() == KEYS::DOWN)
            {
                camera.moveForward(-deltaTime * 5);
                input.pop();
            }
            //left
            else if (input.front() == KEYS::LEFT)
            {
                camera.moveRight(-deltaTime * 5);
                input.pop();
            }
            //right
            else if (input.front() == KEYS::RIGHT)
            {
                camera.moveRight(deltaTime * 5);
                input.pop();
            }
            //SPACE
            else if (input.front() == KEYS::SPACE)
            {
                //transform = glm::translate(transform, glm::vec3(0.001, 0, 0));
                //view = glm::translate(view, glm::vec3(0.0f, 0.0f, -0.001f));
                input.pop();
            }
            //X
            else if (input.front() == KEYS::W)
            {
                //transform = glm::translate(transform, glm::vec3(- 0.001, 0, 0));
                //view = glm::translate(view, glm::vec3(0.0f, 0.0f, 0.001f));
                input.pop();
            }
            else
                input.pop();
        }
    }
};
