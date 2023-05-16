#pragma once
#include "GameEngine/GameObject.h"
#include "GameEngine/DataManager.h"
#include "GameEngine/CubeRenderer.h"
#include "GameEngine/TransformComponent.h"
#include "GameEngine/PhysicsComponent.h"
#include "GameEngine/ShaderComponent.h"
#include "GameEngine/MeshComponent.h"
#include "GameEngine/ColliderComponent.h"
#include "GameEngine/Component.h"
#include "BasicCameraInput.h"
#include "Program.h"

class GameEngine :public Program
{
private:

public:
	BasicCameraInput inputHandler = BasicCameraInput(&_camera);

	float time = 0;

	void Setup() override
	{
		_camera.setPosition(glm::vec3(0, 0, -20));
		_camera.setFOV(70);

	}

	void Run(float deltaTime) override
	{

		if (ImGui::Button("New Cube"))
		{
			int new_id = DM.NewGameObject();
			DM.AddComponent<CubeRenderer>(new_id);
			DM.AddComponent<TransformComponent>(new_id, glm::vec3(0), glm::vec3(2, 1, 0.5));
			DM.AddComponent<PhysicsComponent>(new_id)->ApplyForce(glm::vec3(0, 10, 0));
			DM.AddComponent<ColliderComponent>(new_id);
		}

		if (ImGui::Button("New Buterfly"))
		{
			int new_id = DM.NewGameObject();
			DM.AddComponent<TransformComponent>(new_id);
			DM.AddComponent<ColliderComponent>(new_id);
			DM.AddComponent<ShaderComponent>(new_id, "Shaders/Combined/Obj.hlsl");
			DM.AddComponent<MeshComponent>(new_id, "Assets/butterfly.obj");
		}

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