#pragma once
#include <map>
#include <any>
#include <string>

class Program
{
public:
    // Pure virtual function that must be overridden by derived classes
    virtual void Setup() = 0;
    virtual void Run(float time, Window window) = 0;

};

