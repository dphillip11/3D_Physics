#include "PCH/pch.h"
#include "GameEngine/CollisionManager.h"
#include "GameEngine/DataManager.h"
#include "GameEngine/PhysicsComponent.h"
#include "GameEngine/PrimitiveRenderer.h"
#include "GameEngine/Geometry.h"

#define DEBUG 1

std::queue<collision> CollisionManager::collisionLog;

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

std::unordered_map<int, TransformComponent> CollisionManager::ColliderTransforms;

TransformComponent& CollisionManager::AddColliderTransform(int GameObjectID) {
	ColliderTransforms.emplace(GameObjectID, TransformComponent(GameObjectID));
	auto& transformComponent = ColliderTransforms[GameObjectID];
	return transformComponent;
}

TransformComponent* CollisionManager::GetColliderTransform(int GameObjectID) {
	auto it = ColliderTransforms.find(GameObjectID);
	if (it == ColliderTransforms.end())
		return nullptr;
	return &(it->second);
}

collision CollisionManager::GetCollision(int ID1, int ID2)
{
	collision col;

	col.ID1 = ID1;
	col.ID2 = ID2;
	col.depth = std::numeric_limits<float>::max();

	auto cornersA = DM.GetComponent<ColliderComponent>(ID1)->CalculateOBBCorners();
	auto cornersB = DM.GetComponent<ColliderComponent>(ID2)->CalculateOBBCorners();

#if DEBUG
	PrimitiveRenderer::DrawPoints(cornersA, 5);
	PrimitiveRenderer::DrawPoints(cornersB, 4);
#endif


	auto transformA = GetColliderTransform(ID1);
	auto world_transformA = transformA->GetWorldTransform();
	auto centre1 = GetColliderTransform(col.ID1)->GetWorldPosition();
	auto transformB = GetColliderTransform(ID2);
	auto world_transformB = transformB->GetWorldTransform();

	//check along axes of first cube
	for (auto axis : CubeAxes)
	{
		auto transformed_AxisA = glm::vec3(world_transformA * glm::vec4(0.5f * axis, 1));
		auto normalized_transformed_AxisA = glm::normalize(transformed_AxisA);
		auto transformed_AxisB = glm::vec3(world_transformB * glm::vec4(axis, 1));
		auto normalized_transformed_AxisB = glm::normalize(transformed_AxisB);
		bool isALower1 = true;
		bool isAlower2 = true;
		glm::vec3 contact_point;
		float depthA = CheckSeperatingAxis(normalized_transformed_AxisA, &cornersA[0], &cornersB[0], isALower1, contact_point);
		float depthB = CheckSeperatingAxis(normalized_transformed_AxisB, &cornersA[0], &cornersB[0], isAlower2, contact_point);

		if (depthA < 0 || depthB < 0)
			return col;
		if (depthA < col.depth)
		{
			col.depth = depthA;
			col.normal = isALower1 ? normalized_transformed_AxisA : -normalized_transformed_AxisA;
			col.contact_point = contact_point;
		}
		if (depthB < col.depth)
		{
			col.depth = depthB;
			col.normal = isAlower2 ? normalized_transformed_AxisB : -normalized_transformed_AxisB;
			col.contact_point = contact_point;
		}
	}
	col.valid = true;

#if DEBUG
	PrimitiveRenderer::DrawPoints(std::vector<glm::vec3>{col.contact_point}, 0);
	PrimitiveRenderer::DrawLines(std::vector<glm::vec3>{centre1, col.contact_point}, 3);
#endif

	return col;
}

float CollisionManager::CheckSeperatingAxis(const glm::vec3 axis, const glm::vec3 cornersA[8], const glm::vec3 cornersB[8], bool& isALower, glm::vec3& contact_point)
{
	Geometry::axis_projection limitsA = Geometry::project_on_axis(axis, std::vector<glm::vec3>(cornersA, cornersA + 8));
	Geometry::axis_projection limitsB = Geometry::project_on_axis(axis, std::vector<glm::vec3>(cornersB, cornersB + 8));

	// Check for overlap
	float overlap = std::min(limitsA.max_projection, limitsB.max_projection) - std::max(limitsA.min_projection, limitsB.min_projection);
	isALower = limitsA.max_projection < limitsB.max_projection;

	// Update the contact point based on the corners contributing to the minimum and maximum projections
	if (overlap > 0)
	{
		if (isALower)
			contact_point = limitsA.maximum_point;
		else
			contact_point = limitsA.minimum_point;
	}
	else
	{
		// No overlap, set the contact point to a default value or handle the case as needed
		contact_point = glm::vec3(0.0f); // Default value
	}

	// Return the penetration depth
	return overlap;
}


void CollisionManager::CheckCollisions()
{
	//clear log
	while (!collisionLog.empty())
		collisionLog.pop();
	//fill log
	for (auto it1 = std::begin(ColliderTransforms); it1 != std::end(ColliderTransforms); ++it1)
	{
		auto [id1, transform1] = *it1;
		//only check with higher ID's
		auto it2 = it1;
		std::advance(it2, 1);

		for (; it2 != std::end(ColliderTransforms); ++it2)
		{
			auto [id2, transform2] = *it2;

			collision col = GetCollision(id1, id2);
			if (col.valid)
				collisionLog.push(col);
		}
	}
}

void CollisionManager::Notify()
{
	while (!collisionLog.empty())
	{
		auto col = collisionLog.front();
		collisionLog.pop();

		//NotifyPhysics(col);

	}
}

void CollisionManager::NotifyPhysics(collision col)
{
	DM.GetComponent<PhysicsComponent>(col.ID1)->AddCollision(col);
}