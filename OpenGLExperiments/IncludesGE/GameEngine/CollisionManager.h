
#include "GameEngine/TransformComponent.h"
#include "GameEngine/ColliderComponent.h"

namespace CollisionManager {


	extern std::queue<collision> collisionLog;
	extern std::unordered_map<int, TransformComponent> ColliderTransforms;

	TransformComponent& AddColliderTransform(int GameObjectID);
	TransformComponent* GetColliderTransform(int GameObjectID);

	void CheckCollisions();

	std::vector<glm::vec3> GetCollision_surface_test(int ID1, int ID2);
	collision GetCollision_SAT_test(int ID1, int ID2);

	void NotifyPhysics(collision col);

	void Notify();
}
