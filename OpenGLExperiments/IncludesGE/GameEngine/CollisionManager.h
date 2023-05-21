
#include "GameEngine/TransformComponent.h"
#include "GameEngine/ColliderComponent.h"

namespace CollisionManager {


	extern std::queue<collision> collisionLog;
	extern std::unordered_map<int, TransformComponent> ColliderTransforms;

	TransformComponent& AddColliderTransform(int GameObjectID);
	TransformComponent* GetColliderTransform(int GameObjectID);

	float CheckSeperatingAxis(const glm::vec3 axis, const glm::vec3 cornersA[8], const glm::vec3 cornersB[8]);
	void CheckCollisions();

	collision GetCollision(int ID1, int ID2);

	void NotifyPhysics(collision col);

	void Notify();
	/*void Update(float deltaTime) {
		CheckCollisions();
	}*/

}

//private:
//
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
//	std::unordered_map<std::size_t, CollisionEventHandler> collisionEventHandlers;
//
//	bool CheckCollision(const ColliderComponent& collider1, const ColliderComponent& collider2) {
//		// Perform collision detection logic using the colliders
//		// Return true if a collision occurs, false otherwise
//		// ...
//		return false; // Placeholder, replace with actual collision detection logic
//	}

	//void NotifyCollisionEvent(int collider1_object_id, int collider2_object_id) {
	//	// Get the collider components for the collided objects
	//	auto& DM = DataManager::getInstance();
	//	auto collider1 = DM.GetComponent<ColliderComponent>(collider1_object_id);
	//	auto collider2 = DM.GetComponent<ColliderComponent>(collider2_object_id);

	//	// Get the collider types for the collided objects
	//	auto collider1_type_id = DM.GetTypeID<ColliderComponent>();
	//	auto collider2_type_id = DM.GetTypeID<ColliderComponent>();

	//	// Check if there is a registered collision event handler for the collider types
	//	auto handler1_it = collisionEventHandlers.find(collider1_type_id);
	//	auto handler2_it = collisionEventHandlers.find(collider2_type_id);

	//	// Call the collision event handlers if they are registered
	//	if (handler1_it != collisionEventHandlers.end())
	//		handler1_it->second(collider1_object_id, collider2_object_id);

	//	if (handler2_it != collisionEventHandlers.end())
	//		handler2_it->second(collider2_object_id, collider1_object_id);
	//}
