#include "PCH/pch.h"
#include "GameEngine/CollisionManager.h"
#include "GameEngine/DataManager.h"
#include "GameEngine/PhysicsComponent.h"
#include "GameEngine/PrimitiveRenderer.h"
#include "GameEngine/Geometry.h"

//draw collisions
#define DEBUG 1
//use SAT or surface test
#define SAT 1


std::queue<collision> CollisionManager::collisionLog;
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

collision CollisionManager::GetCollision_surface_test(int ID1, int ID2)
{
	collision col;

	col.ID1 = ID1;
	col.ID2 = ID2;

	auto IDs = { ID1,ID2 };

	for (auto ID : IDs)
	{
		auto other_ID = ID == ID1 ? ID2 : ID1;

		auto transform = GetColliderTransform(ID);
		auto world_transform = transform->GetWorldTransform();
		auto pos = transform->GetWorldPosition();

		//prepare points for testing
		std::vector<glm::vec3> points;
		//add face points
		Geometry::generate_face_points(GetColliderTransform(other_ID)->GetWorldTransform(), points);
		//add corners
		DM.GetComponent<ColliderComponent>(other_ID)->CalculateOBBCorners(points);
		//6 faces, 8 vertices
		assert(points.size() == 14);

		col.valid = Geometry::test_points_inside_cube(world_transform, points, col.contact_point);

		if (col.valid)
		{
			col.normal = glm::normalize(col.contact_point - pos);
#if DEBUG
			PrimitiveRenderer::DrawLines(std::vector<glm::vec3>({ pos, col.contact_point }), 1);
			PrimitiveRenderer::DrawPoints(std::vector<glm::vec3>({ col.contact_point }), 3);
#endif
			return col;
		}
	}
	return col;
}

collision CollisionManager::GetCollision_SAT_test(int ID1, int ID2)
{
	collision col;

	col.ID1 = ID1;
	col.ID2 = ID2;

	std::vector<glm::vec3> cornersA;
	DM.GetComponent<ColliderComponent>(ID1)->CalculateOBBCorners(cornersA);
	std::vector<glm::vec3> cornersB;
	DM.GetComponent<ColliderComponent>(ID2)->CalculateOBBCorners(cornersB);

	auto transformA = GetColliderTransform(ID1);
	auto world_transformA = transformA->GetWorldTransform();

	auto transformB = GetColliderTransform(ID2);
	auto world_transformB = transformB->GetWorldTransform();

	std::vector<glm::vec3> axes;
	Geometry::generate_SAT_axes_for_cube(world_transformA, axes);
	Geometry::generate_SAT_axes_for_cube(world_transformB, axes);
	assert(axes.size() == 14);

	float minimim_overlap = std::numeric_limits<float>().max();

	for (auto axis : axes)
	{
		glm::vec3 contact_point;
		bool isAlower;
		auto overlap = Geometry::test_seperating_axis(axis, cornersA, cornersB, contact_point, isAlower);
		if (overlap < 0)
			return col;
		if (overlap < minimim_overlap)
		{
			minimim_overlap = overlap;
			col.contact_point = contact_point;
			col.normal = isAlower ? axis : -axis;
		}
	}
	col.valid = true;
	col.depth = minimim_overlap;
#if DEBUG
	auto centre = transformA->GetWorldPosition();
	PrimitiveRenderer::DrawLines(std::vector<glm::vec3>({ centre, centre + col.depth * col.normal }), 1);
	PrimitiveRenderer::DrawPoints(std::vector<glm::vec3>({ centre }), 3);
#endif
	return col;

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
#if SAT
			collision col = GetCollision_SAT_test(id1, id2);
#else
			collision col = GetCollision_surface_test(id1, id2);
#endif
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

		NotifyPhysics(col);

	}
}

void CollisionManager::NotifyPhysics(collision col)
{
	DM.GetComponent<PhysicsComponent>(col.ID1)->AddCollision(col);
}