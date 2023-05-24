#include "PCH/pch.h"
#include "GameEngine/PhysicsComponent.h"
#include "GameEngine/DataManager.h"
#include "GameEngine/Quaternion.h"


PhysicsComponent::PhysicsComponent(int GameObjectID, float mass, const glm::vec3& gravity)
	: m_mass(mass), m_gravity(gravity), m_velocity(0.0f), m_acceleration(0.0f), Component(GameObjectID),
	m_transform(DM.GetComponent<TransformComponent>(GameObjectID)) {}

void PhysicsComponent::Update(float deltaTime) {


	if (!isStatic)
	{

		// Apply gravity to the acceleration
		m_acceleration += m_gravity;

		// Apply the total force to the acceleration
		m_acceleration += m_totalForce / m_mass;

		// Update velocity based on acceleration and time
		m_velocity += m_acceleration * deltaTime;

		// Update position based on velocity and time
		glm::vec3 displacement = m_velocity * deltaTime;
		m_transform->Translate(displacement);

		// Update angular velocity based on torque and time
		m_angularAcceleration = Quaternion::ScaleQuaternion(m_torque, 1 / m_mass) * m_angularAcceleration;
		m_angularVelocity += 0.5f * m_angularAcceleration * deltaTime;
		glm::quat deltaRotation = m_angularVelocity * deltaTime;
		m_transform->Rotate(deltaRotation);

		// Reset acceleration, total force, and torque for the next frame
		m_acceleration = glm::vec3(0.0f);
		m_totalForce = glm::vec3(0.0f);
		m_torque = glm::identity<glm::quat>();
		m_angularAcceleration = glm::identity<glm::quat>();
	}

	ResolveCollisions();

}

void PhysicsComponent::ResolveCollisions() {
	while (!m_collisionLog.empty()) {
		collision col = m_collisionLog.front();
		m_collisionLog.pop();
		auto B_physics = DM.GetComponent<PhysicsComponent>(col.ID2);
		auto A_transform = DM.GetComponent<TransformComponent>(col.ID1);
		auto B_transform = DM.GetComponent<TransformComponent>(col.ID2);
		auto A_colliderPos = CollisionManager::GetColliderTransform(col.ID1)->GetWorldPosition();
		auto B_colliderPos = CollisionManager::GetColliderTransform(col.ID2)->GetWorldPosition();

		//adjust position
		A_transform->Translate(-0.51f * col.depth * col.normal);
		B_transform->Translate(0.51f * col.depth * col.normal);
		// Calculate momentum conservation
		glm::vec3 relativeVelocity = m_velocity - B_physics->m_velocity; // Relative velocity of the objects
		float collisionSpeed = glm::dot(relativeVelocity, col.normal); // Collision speed along the normal direction
		float elasticity = 0.4f;
		glm::vec3 normalImpulse = -(1 + elasticity) * col.normal * collisionSpeed / (m_mass + B_physics->m_mass); // Calculate impulse using masses, relative velocity, and coefficient of restitution
		m_velocity -= normalImpulse * B_physics->m_mass; // Update velocity of object 1
		B_physics->m_velocity += normalImpulse * m_mass; // Update velocity of object 2

		ApplyTorque(glm::cross((col.contact_point) - A_colliderPos, normalImpulse));
		B_physics->ApplyTorque(glm::cross((col.contact_point) - B_colliderPos, normalImpulse));
	}
}



void PhysicsComponent::Render() {

}
