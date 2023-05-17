#include "PCH/pch.h"
#include "../Programs/GameEngine.h"
#include "GameEngine/TransformComponent.h"
#include "GameEngine/PhysicsComponent.h"
#include "GameEngine/RendererComponent.h"
#include "GameEngine/ColliderComponent.h"
#include "GameEngine/ShaderComponent.h"
#include "GameEngine/MeshComponent.h"
#include "GameEngine/FileManager.h"

void GameEngine::Spawn(Prefabs p)
{
	int new_id;

	auto addComponents = [&new_id](std::string name) {
		new_id = DM.NewGameObject(name);
		DM.AddComponent<TransformComponent>(new_id);
		DM.AddComponent<PhysicsComponent>(new_id)->ApplyForce(glm::vec3(0, 10, 0));
		DM.AddComponent<ColliderComponent>(new_id);
		DM.AddComponent<RendererComponent>(new_id);
		DM.AddComponent<ShaderComponent>(new_id, GetFilePath(Shaders::Obj));
	};

	switch (p)
	{
	case(Prefabs::HARE):
		addComponents("Hare");
		DM.AddComponent<MeshComponent>(new_id, GetFilePath(Models::Hare));
		break;
	case(Prefabs::CUBE):
		addComponents("Cube");
		DM.AddComponent<MeshComponent>(new_id, GetFilePath(Models::Cube));
		break;
	case(Prefabs::BUTTERFLY):
		addComponents("Butterfly");
		DM.AddComponent<MeshComponent>(new_id, GetFilePath(Models::Butterfly));
		break;
	case(Prefabs::HAND):
		addComponents("Hand");
		DM.AddComponent<MeshComponent>(new_id, GetFilePath(Models::Hand));
		break;
	case(Prefabs::ROBOT):
		addComponents("Robot");
		DM.AddComponent<MeshComponent>(new_id, GetFilePath(Models::Robot));
		break;
	case(Prefabs::TAXI):
		addComponents("Taxi");
		DM.AddComponent<MeshComponent>(new_id, GetFilePath(Models::Taxi));
		break;
	case(Prefabs::TREE):
		addComponents("Tree");
		DM.AddComponent<MeshComponent>(new_id, GetFilePath(Models::Tree));
		break;
	}
}





