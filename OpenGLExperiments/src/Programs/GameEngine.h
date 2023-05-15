#pragma once
#include "GameEngine/GameObject.h"
#include "GameEngine/DataManager.h"
#include "GameEngine/CubeRenderer.h"
#include "GameEngine/TransformComponent.h"
#include "BasicCameraInput.h"

class GameEngine :public Program
{
private:

public:
	BasicCameraInput inputHandler = BasicCameraInput(&_camera);

	float time = 0;

	void Setup() override
	{
		_camera.setPosition(glm::vec3(0, 0, -5));
		int new_id = DM.NewGameObject();
		DM.AddComponent<CubeRenderer>(new_id);
		DM.AddComponent<TransformComponent>(new_id);

		new_id = DM.NewGameObject();
		DM.AddComponent<CubeRenderer>(new_id);
		DM.AddComponent<TransformComponent>(new_id);
	}

	void Run(float deltaTime) override
	{
		for (auto& [id, gameObject] : DM.GameObjects) {
			gameObject->Update(deltaTime);
			gameObject->Render();
		}
	}

	InputObserver* getInputHandler()
	{
		return &inputHandler;
	}
};