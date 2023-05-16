
#include "GameEngine/TransformComponent.h"
#include "GameEngine/ColliderComponent.h"

class CollisionManager {
public:
	std::unordered_map<int, TransformComponent> ColliderTransforms;

	TransformComponent* AddCollider(int GameObjectID) {
		auto& transformComponent = ColliderTransforms[GameObjectID];
		// Initialize or modify the transformComponent object as needed
		return &transformComponent;
	}
};

//	using CollisionEventHandler = std::function<void(int, int)>;
//
//	void AddCollisionEventHandler(std::size_t collider_type_id, CollisionEventHandler handler) {
//		collisionEventHandlers[collider_type_id] = handler;
//	}
//
//	void RemoveCollisionEventHandler(std::size_t collider_type_id) {
//		collisionEventHandlers.erase(collider_type_id);
//	}
//
//	void Update(float deltaTime) {
//		for (const auto& objectID1 : DM.FilterObjectsByComponent<TransformComponent>()) {
//			const auto& collider1 = DM.GetComponent<ColliderComponent>(objectID1);
//			if (collider1 == nullptr)
//				continue;
//
//			for (const auto& objectID2 : DM.GetActiveObjects()) {
//				if (objectID1 == objectID2)
//					continue;
//
//				const auto& collider2 = DM.GetComponent<ColliderComponent>(objectID2);
//				if (collider2 == nullptr)
//					continue;
//
//				if (CheckCollision(*collider1, *collider2)) {
//					NotifyCollisionEvent(objectID1, objectID2);
//				}
//			}
//		}
//	}
//
//private:
//	std::unordered_map<std::size_t, CollisionEventHandler> collisionEventHandlers;
//
//	bool CheckCollision(const ColliderComponent& collider1, const ColliderComponent& collider2) {
//		// Perform collision detection logic using the colliders
//		// Return true if a collision occurs, false otherwise
//		// ...
//		return false; // Placeholder, replace with actual collision detection logic
//	}
//
//	void NotifyCollisionEvent(int collider1_object_id, int collider2_object_id) {
//		// Get the collider components for the collided objects
//		auto& DM = DataManager::getInstance();
//		auto collider1 = DM.GetComponent<ColliderComponent>(collider1_object_id);
//		auto collider2 = DM.GetComponent<ColliderComponent>(collider2_object_id);
//
//		// Get the collider types for the collided objects
//		auto collider1_type_id = DM.GetTypeID<ColliderComponent>();
//		auto collider2_type_id = DM.GetTypeID<ColliderComponent>();
//
//		// Check if there is a registered collision event handler for the collider types
//		auto handler1_it = collisionEventHandlers.find(collider1_type_id);
//		auto handler2_it = collisionEventHandlers.find(collider2_type_id);
//
//		// Call the collision event handlers if they are registered
//		if (handler1_it != collisionEventHandlers.end())
//			handler1_it->second(collider1_object_id, collider2_object_id);
//
//		if (handler2_it != collisionEventHandlers.end())
//			handler2_it->second(collider2_object_id, collider1_object_id);
//	}
//};