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
		BM.gravity = 98;
		BM.min_restitution = 0.7;
		BM.max_restitution = 0.75;
		BM.max_bucket_size = 500;
		BM.spawnObjects(8000);
		BM.generateBuffers();
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