#pragma once
#include <map>
#include <any>
#include <string>

class Program
{
public:
    std::map<std::string, std::any> context;

    // Pure virtual function that must be overridden by derived classes
    virtual void Setup() = 0;
    virtual void Run() = 0;

};

