
#include "Camera.h"

class Program
{
public:
    // Pure virtual function that must be overridden by derived classes
    virtual void Setup(Camera* camera) = 0;
    virtual void Run(float time, Window window) = 0;

};

