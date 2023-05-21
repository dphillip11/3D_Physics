#include "PCH/pch.h"
#include "GameEngine/PrefabManager.h"
#include "GameEngine/TransformComponent.h"
#include "GameEngine/PhysicsComponent.h"
#include "GameEngine/RendererComponent.h"
#include "GameEngine/ColliderComponent.h"
#include "GameEngine/ShaderComponent.h"
#include "GameEngine/MeshComponent.h"
#include "GameEngine/FileManager.h"
#include "GameEngine/DataManager.h"

namespace PrefabManager {

	void Spawn(Prefabs p)
	{
		int new_id;

		auto addComponents = [&new_id](std::string name) {
			new_id = DM.NewGameObject(name);
			DM.AddComponent<TransformComponent>(new_id);
			DM.AddComponent<PhysicsComponent>(new_id);
			DM.AddComponent<RendererComponent>(new_id);
			DM.AddComponent<ShaderComponent>(new_id, GetFilePath(Shaders::Obj));
		};

		switch (p)
		{
		case(Prefabs::HARE):
			addComponents("Hare");
			DM.AddComponent<MeshComponent>(new_id, GetFilePath(Models::Hare));
			DM.AddComponent<ColliderComponent>(new_id);
			break;
		case(Prefabs::CUBE):
			addComponents("Cube");
			DM.AddComponent<MeshComponent>(new_id, GetFilePath(Models::Cube));
			DM.AddComponent<ColliderComponent>(new_id);
			break;
		case(Prefabs::BUTTERFLY):
			addComponents("Butterfly");
			DM.AddComponent<MeshComponent>(new_id, GetFilePath(Models::Butterfly));
			DM.AddComponent<ColliderComponent>(new_id);
			break;
		case(Prefabs::HAND):
			addComponents("Hand");
			DM.AddComponent<MeshComponent>(new_id, GetFilePath(Models::Hand));
			DM.AddComponent<ColliderComponent>(new_id);
			break;
		case(Prefabs::ROBOT):
			addComponents("Robot");
			DM.AddComponent<MeshComponent>(new_id, GetFilePath(Models::Robot));
			DM.AddComponent<ColliderComponent>(new_id);
			break;
		case(Prefabs::TAXI):
			addComponents("Taxi");
			DM.AddComponent<MeshComponent>(new_id, GetFilePath(Models::Taxi));
			DM.AddComponent<ColliderComponent>(new_id);
			break;
		case(Prefabs::TREE):
			addComponents("Tree");
			DM.AddComponent<MeshComponent>(new_id, GetFilePath(Models::Tree));
			DM.AddComponent<ColliderComponent>(new_id);
			break;
		case(Prefabs::AIRPLANE):
			addComponents("Airplane");
			DM.AddComponent<MeshComponent>(new_id, GetFilePath(Models::Airplane));
			DM.AddComponent<ColliderComponent>(new_id);
			break;
		}
	}
}