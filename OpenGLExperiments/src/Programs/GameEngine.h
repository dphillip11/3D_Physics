#pragma once
#include "GameEngine/GameObject.h"
#include "GameEngine/DataManager.h"
#include "GameEngine/CollisionManager.h"
#include "BasicCameraInput.h"
#include "Program.h"
#include <vector>

class GameEngine :public Program
{
private:

public:

	BasicCameraInput inputHandler = BasicCameraInput(&_camera);

	float time = 0;

	void Setup() override
	{
		_camera.setPosition(glm::vec3(0, 0, -20));
		_camera.isLockedOn = true;
		_camera.setFOV(70);
	}


	void Run(float deltaTime) override
	{

		std::vector<int> deleteIDs;

		for (auto& [id, gameObject] : DM.GameObjects)
		{
			if (gameObject->deleted)
				deleteIDs.push_back(gameObject->id_);

			gameObject->Update(deltaTime);
			gameObject->Render();
		}

		for (auto id : deleteIDs)
		{
			DM.RemoveGameObject(id);
		}

		CollisionManager::CheckCollisions();

	}

	InputObserver* getInputHandler()
	{
		return &inputHandler;
	}
};