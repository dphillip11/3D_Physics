#pragma once
#include "../Classes/Window.h"
#include "../Classes/BallManager.h"
#include "../InputHandlers/BallPhysicsInput.h"

class BallPhysics :public Program
{
public:

	BallManager BM;
	Camera camera = Camera(glm::vec3(0, 0, -300), glm::vec3(0, 0, 0));
	BallPhysicsInput inputHandler = BallPhysicsInput(&camera, &BM);
	float time = 0;
	
	void Setup()
	{
		camera.setFOV(75);
		camera.zoomSpeed = 10;
		camera.moveSpeed = 1;
		BM.populateColors(100);
		BM.gravity = 9.8;
		BM.spawnObjects(2000);
	}
	void Run(float deltaTime)
	{
		time += deltaTime;
		BM.drawObjects(camera);
		BM.update(deltaTime);
	}

	InputObserver* getInputHandler()
	{
		return &inputHandler;
	}
};