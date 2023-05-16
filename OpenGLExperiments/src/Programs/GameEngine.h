#pragma once
#include "GameEngine/GameObject.h"
#include "GameEngine/DataManager.h"
#include "BasicCameraInput.h"
#include "Program.h"

class GameEngine :public Program
{
private:

public:
	enum class Prefabs {

		HARE,
		HAND,
		TAXI,
		CUBE,
		BUTTERFLY,
		ROBOT,
		TREE,

	};

	BasicCameraInput inputHandler = BasicCameraInput(&_camera);

	float time = 0;

	void Setup() override
	{
		_camera.setPosition(glm::vec3(0, 0, -20));
		_camera.setFOV(70);

	}

	void Spawn(Prefabs P);

	void Run(float deltaTime) override
	{
		static Prefabs selectedPrefab = Prefabs::HARE; // default selection

		const char* prefabLabels[] = { "HARE", "HAND", "TAXI", "CUBE", "BUTTERFLY", "ROBOT", "TREE" };


		if (ImGui::BeginCombo("Select Prefab", prefabLabels[(static_cast<int>(selectedPrefab))]))
		{
			for (int i = 0; i < static_cast<int>(Prefabs::TREE) + 1; i++)
			{
				Prefabs prefab = static_cast<Prefabs>(i);
				bool isSelected = (selectedPrefab == prefab);
				if (ImGui::Selectable(prefabLabels[i], isSelected))
				{
					selectedPrefab = prefab;
				}
				if (isSelected)
				{
					ImGui::SetItemDefaultFocus();
				}
			}
			ImGui::EndCombo();
		}

		if (ImGui::Button("Spawn"))
		{
			Spawn(selectedPrefab);
		}

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
	}

	InputObserver* getInputHandler()
	{
		return &inputHandler;
	}
};