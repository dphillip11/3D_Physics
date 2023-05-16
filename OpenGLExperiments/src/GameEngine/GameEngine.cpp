#include "PCH/pch.h"
#include "../Programs/GameEngine.h"
#include "GameEngine/TransformComponent.h"
#include "GameEngine/PhysicsComponent.h"
#include "GameEngine/RendererComponent.h"
#include "GameEngine/ColliderComponent.h"
#include "GameEngine/ShaderComponent.h"
#include "GameEngine/MeshComponent.h"

void GameEngine::Spawn(Prefabs p)
{
	int new_id = DM.NewGameObject();
	DM.AddComponent<TransformComponent>(new_id, glm::vec3(0), glm::vec3(2, 1, 0.5));
	DM.AddComponent<PhysicsComponent>(new_id)->ApplyForce(glm::vec3(0, 10, 0));
	DM.AddComponent<ColliderComponent>(new_id);
	DM.AddComponent<RendererComponent>(new_id);
	DM.AddComponent<ShaderComponent>(new_id, "Shaders/Combined/Obj.hlsl");

	switch (p)
	{
	case(Prefabs::HARE):
		DM.AddComponent<MeshComponent>(new_id, "Assets/hare.obj");
		break;
	case(Prefabs::CUBE):
		DM.AddComponent<MeshComponent>(new_id, "Assets/cube.obj");
		break;
	case(Prefabs::BUTTERFLY):
		DM.AddComponent<MeshComponent>(new_id, "Assets/butterfly.obj");
		break;
	case(Prefabs::HAND):
		DM.AddComponent<MeshComponent>(new_id, "Assets/hand.obj");
		break;
	case(Prefabs::ROBOT):
		DM.AddComponent<MeshComponent>(new_id, "Assets/robot.obj");
		break;
	case(Prefabs::TAXI):
		DM.AddComponent<MeshComponent>(new_id, "Assets/taxi.obj");
		break;
	case(Prefabs::TREE):
		DM.AddComponent<MeshComponent>(new_id, "Assets/tree.obj");
		break;
	}
}





