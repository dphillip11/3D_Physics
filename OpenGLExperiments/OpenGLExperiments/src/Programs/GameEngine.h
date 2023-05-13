#pragma once
#include "GameEngine/DataManager.h"
#include <range>


class GameEngine :public Program
{
private:

public:
	BasicCameraInput inputHandler = BasicCameraInput(&_camera);

	float time = 0;

	void Setup() override
	{
		_camera.setPosition(glm::vec3(0, -5, 0));
		int new_id = DM::NewGameObject();
		DM::addComponent(new_id, DM::CubeRenderers);
		DM::addComponent(new_id, DM::TransformComponents);

		new_id = DM::NewGameObject();
		DM::addComponent(new_id, DM::CubeRenderers);
		DM::addComponent(new_id, DM::TransformComponents);
	}

	void Run(float deltaTime) override
	{
		for (auto& [id, gameObject] : DM::GameObjects) {
			gameObject->Update(deltaTime);
			gameObject->Render();
		}
	}

	InputObserver* getInputHandler()
	{
		return &inputHandler;
	}
};