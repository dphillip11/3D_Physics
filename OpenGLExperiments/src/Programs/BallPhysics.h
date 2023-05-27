#pragma once
#include "BallManager.h"
#include "BallPhysicsInput.h"

class BallPhysics :public Program
{
public:

	BallManager BM;
	BallPhysicsInput inputHandler = BallPhysicsInput(&_camera, &BM);
	float time = 0;

	void Setup()
	{
		_camera.setPosition(glm::vec3(0, 0, -300));
		_camera.setTarget(glm::vec3(0, 0, 0));
		_camera.setFOV(75);
		_camera.zoomSpeed = 10;
		_camera.moveSpeed = 1;
		BM.gravity = 98;
		BM.min_restitution = 0.8f;
		BM.max_restitution = 0.95f;
		BM.max_bucket_size = 500;
		BM.spawnObjects(8000);
		BM.generateBuffers();
	}
	void Run(float deltaTime)
	{
		time += deltaTime;
		BM.drawObjects(_camera);
		BM.update(deltaTime);
	}

	InputObserver* getInputHandler()
	{
		return &inputHandler;
	}
};