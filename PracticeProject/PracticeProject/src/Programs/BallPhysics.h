#pragma once
#include "../Classes/Window.h"

class BallPhysics :public Program
{
public:

	BallManager BM;
	Camera* camera = nullptr;
	float time = 0;
	float spawned = false;
	
	void Setup(Camera* _camera)
	{
		BM.populateColors(100);
		BM.gravity = 9.8;
		BM.collisionEfficiency = 0.8;
		camera = _camera;
		BM.spawnObjects(2000);
	}
	void Run(float _time, Window window)
	{
		float deltaTime = _time - time;
		time = _time;
		if (time > 10 && !spawned)
		{
			BM.spawnObject(glm::vec3(0, BM.boundarySize - 20, 0), glm::vec3(0, -100, 0), 20);
			spawned = true;
		}
		BM.drawObjects(*camera);
		BM.update(deltaTime);
	}
};