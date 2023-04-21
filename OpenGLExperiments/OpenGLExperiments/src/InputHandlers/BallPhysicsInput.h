#pragma once
#include "../Classes/Camera.h"
#include "../Classes/InputObserver.h"
#include "../Classes/BallManager.h"

class BallPhysicsInput : public InputObserver
{
public:
    Camera* camera;
    BallManager* BM;
    BallPhysicsInput(Camera* new_camera, BallManager* new_BM) : camera(new_camera), BM(new_BM) {};
    void onKeyPress(int key, float deltaTime);
    void onMouseScroll(float scroll_value, float deltaTime);
    void onMousePress(float deltaTime);
    void onMouseMove(float dx, float dy, float deltaTime);
};

