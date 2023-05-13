#pragma once
#include "GameEngine/GameObject.h"
#include "GameEngine/CubeRenderer.h"
#include "GameEngine/TransformComponent.h"

class GameEngine :public Program
{
private:

public:
	std::vector<std::unique_ptr<GameObject>> gameObjects_;
	BasicCameraInput inputHandler = BasicCameraInput(&_camera);

	float time = 0;

	void Setup() override
	{
		_camera.setPosition(glm::vec3(0, -5, 0));
		auto new_object = std::make_unique<GameObject>();
		new_object->AddComponent<CubeRenderer>();
		new_object->AddComponent<TransformComponent>();

		gameObjects_.push_back(std::move(new_object));

		auto new_object2 = std::make_unique<GameObject>();
		//new_object2->AddComponent<CubeRenderer>();
		new_object2->AddComponent<TransformComponent>();

		gameObjects_.push_back(std::move(new_object2));
	}

	void Run(float deltaTime) override
	{
		for (auto& object : gameObjects_) {
			object->Update(deltaTime);
			object->Render();
		}
	}

	InputObserver* getInputHandler()
	{
		return &inputHandler;
	}
};