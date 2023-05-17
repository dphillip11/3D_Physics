#include "PCH/pch.h"
#include "GameEngine/CollisionManager.h"

namespace CollisionManager {

	std::unordered_map<int, TransformComponent> ColliderTransforms;

	TransformComponent& AddCollider(int GameObjectID) {
		auto& transformComponent = ColliderTransforms[GameObjectID];
		// Initialize or modify the transformComponent object as needed
		return transformComponent;
	}
}