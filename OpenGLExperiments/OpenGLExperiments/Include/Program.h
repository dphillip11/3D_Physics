#pragma once
#include "InputObserver.h"
#include "Camera.h"

class Program
{
public:
    virtual InputObserver* getInputHandler() = 0;
    // Pure virtual function that must be overridden by derived classes
    virtual void Setup() = 0;
    virtual void Run(float deltaTime) = 0;

};

