#include "PCH/pch.h"
#include "GameEngine/CollisionManager.h"
#include "GameEngine/DataManager.h"

namespace CollisionManager {

	struct collision {
		glm::vec3 contact_point;
		glm::vec3 normal;
		float depth = 0;
		bool valid = false;
		int ID1;
		int ID2;
	};

	//normalized axes
	constexpr glm::vec3 CubeAxes[7] = {
		//parallel to centre to centre of faces
		glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 1.0f),
		//from centre to corners on one side
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(-1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, -1.0f, 1.0f),
		glm::vec3(-1.0f, -1.0f, 1.0f)
	};

	constexpr glm::vec3 CubeCorners[8] = {
		glm::vec3(0.5f, 0.5f, 0.5f),
		glm::vec3(0.5f, -0.5f, 0.5f),
		glm::vec3(-0.5f, -0.5f, 0.5f),
		glm::vec3(-0.5f, 0.5f, 0.5f),
		glm::vec3(0.5f, 0.5f, -0.5f),
		glm::vec3(0.5f, -0.5f, -0.5f),
		glm::vec3(-0.5f, -0.5f, -0.5f),
		glm::vec3(-0.5f, 0.5f, -0.5f)
	};

	std::unordered_map<int, TransformComponent> ColliderTransforms;

	TransformComponent& AddColliderTransform(int GameObjectID) {
		ColliderTransforms.emplace(GameObjectID, TransformComponent(GameObjectID));
		auto& transformComponent = ColliderTransforms[GameObjectID];
		return transformComponent;
	}

	TransformComponent* GetColliderTransform(int GameObjectID) {
		auto it = ColliderTransforms.find(GameObjectID);
		if (it == ColliderTransforms.end())
			return nullptr;
		return &(it->second);
	}

	collision GetCollision(int ID1, int ID2)
	{
		collision col;

		if (ID2 <= ID1)
			return col;

		col.ID1 = ID1;
		col.ID2 = ID2;
		col.depth = std::numeric_limits<float>::max();

		auto cornersA = DM.GetComponent<ColliderComponent>(ID1)->CalculateOBBCorners();
		auto cornersB = DM.GetComponent<ColliderComponent>(ID2)->CalculateOBBCorners();
		auto transformA = GetColliderTransform(ID1);
		auto world_transformA = transformA->GetWorldTransform();
		auto transformB = GetColliderTransform(ID2);
		auto world_transformB = transformB->GetWorldTransform();

		//check along axes of first cube
		for (auto axis : CubeAxes)
		{
			auto transformed_AxisA = glm::normalize(glm::vec3(world_transformA * glm::vec4(axis, 1)));
			auto transformed_AxisB = glm::normalize(glm::vec3(world_transformB * glm::vec4(axis, 1)));

			float depthA = CheckSeperatingAxis(transformed_AxisA, &cornersA[0], &cornersB[0]);
			float depthB = CheckSeperatingAxis(transformed_AxisB, &cornersA[0], &cornersB[0]);

			if (depthA < 0 || depthB < 0)
				return col;
			if (depthA < col.depth)
			{
				col.depth = depthA;
				col.normal = transformed_AxisA;
			}
			if (depthB < col.depth)
			{
				col.depth = depthB;
				col.normal = transformed_AxisB;
			}
		}
		col.valid = true;
		std::cout << col.depth << std::endl;
		auto pos = GetColliderTransform(ID1)->GetWorldPosition();
		col.contact_point = pos + (col.normal * col.depth);

		return col;
	}

	float CheckSeperatingAxis(const glm::vec3 axis, const glm::vec3 cornersA[8], const glm::vec3 cornersB[8])
	{
		// Initialize minimum and maximum projections
		float minProjectionA = std::numeric_limits<float>::max();
		float maxProjectionA = -std::numeric_limits<float>::max();
		float minProjectionB = std::numeric_limits<float>::max();
		float maxProjectionB = -std::numeric_limits<float>::max();

		// Compute the projections for object A
		for (int i = 0; i < 8; ++i)
		{
			float projection = glm::dot(cornersA[i], axis);
			minProjectionA = std::min(minProjectionA, projection);
			maxProjectionA = std::max(maxProjectionA, projection);
		}

		// Compute the projections for object B
		for (int i = 0; i < 8; ++i)
		{
			float projection = glm::dot(cornersB[i], axis);
			minProjectionB = std::min(minProjectionB, projection);
			maxProjectionB = std::max(maxProjectionB, projection);
		}

		// Check for overlap
		float overlap = std::min(maxProjectionA, maxProjectionB) - std::max(minProjectionA, minProjectionB);

		// Return the penetration depth
		return overlap;

	}

	void CheckCollisions()
	{
		for (auto [id1, transform1] : ColliderTransforms)
		{
			for (auto [id2, transform2] : ColliderTransforms)
			{
				collision col = GetCollision(id1, id2);
				//if (col.valid)
					//std::cout << "collision: " << col.contact_point.x << ", " << col.contact_point.y << ", " << col.contact_point.z << std::endl;
			}
		}
	}
}