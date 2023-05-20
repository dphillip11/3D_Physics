#include "PCH/pch.h"
#include "GameEngine/PhysicsComponent.h"
#include "GameEngine/DataManager.h"

PhysicsComponent::PhysicsComponent(int GameObjectID, float mass, const glm::vec3& gravity)
	: m_mass(mass), m_gravity(gravity), m_velocity(0.0f), m_acceleration(0.0f), Component(GameObjectID),
	m_transform(DM.GetComponent<TransformComponent>(GameObjectID)) {}

void PhysicsComponent::Update(float deltaTime) {
	if (isStatic)
		return;

	// Apply gravity to the acceleration
	m_acceleration += m_gravity;

	// Apply the total force to the acceleration
	m_acceleration += m_totalForce / m_mass;

	// Update velocity based on acceleration and time
	m_velocity += m_acceleration * deltaTime;

	// Update position based on velocity and time
	glm::vec3 displacement = m_velocity * deltaTime;
	m_transform->Translate_World(displacement);

	// Reset acceleration and total force for the next frame
	m_acceleration = glm::vec3(0.0f);
	m_totalForce = glm::vec3(0.0f);

}

void PhysicsComponent::Render() {

}
