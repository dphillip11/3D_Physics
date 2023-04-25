#pragma once

class InputObserver {
public:
    virtual void onKeyPress(int key, float deltaTime) = 0;
    virtual void onMouseScroll(float scroll_value, float deltaTime) = 0;
    virtual void onMousePress(float deltaTime) = 0;
    virtual void onMouseMove(float dx, float dy, float deltaTime) = 0;
};