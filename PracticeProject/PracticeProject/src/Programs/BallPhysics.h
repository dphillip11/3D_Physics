#pragma once
#include "../Classes/Window.h"

class BallPhysics :public Program
{
public:

	BallManager BM;
	Camera* camera = nullptr;
	float time = 0;
	
	void Setup(Camera* _camera)
	{
		BM.populateColors(100);
		camera = _camera;
		BM.spawnObjects(5000);
	}
	void Run(float _time, Window window)
	{
		float deltaTime = _time - time;
		time = _time;
		BM.drawObjects(*camera);
		BM.update(deltaTime);
	}
};