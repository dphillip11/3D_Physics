#include "PCH/pch.h"
#include "GameEngine/CollisionManager.h"

namespace CollisionManager {

	std::unordered_map<int, TransformComponent> ColliderTransforms;

	TransformComponent& AddCollider(int GameObjectID) {
		ColliderTransforms.emplace(GameObjectID, TransformComponent(GameObjectID));
		auto& transformComponent = ColliderTransforms[GameObjectID];
		return transformComponent;
	}

	TransformComponent* GetCollider(int GameObjectID) {
		auto it = ColliderTransforms.find(GameObjectID);
		if (it == ColliderTransforms.end())
			return nullptr;
		return &(it->second);
	}
}