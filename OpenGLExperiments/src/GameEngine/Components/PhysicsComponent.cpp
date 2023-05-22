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
		// Calculate the relative velocity of the two colliding objects
		glm::vec3 relativeVelocity = m_velocity - B_physics->GetVelocity();

		// Calculate the relative velocity in terms of the collision normal
		float relativeVelocityAlongNormal = glm::dot(relativeVelocity, col.normal);

		// Check if the objects are moving away from each other
		if (relativeVelocityAlongNormal > 0) {
			continue;  // No collision response needed
		}

		// Calculate the restitution coefficient (a measure of elasticity)
		float restitution = 0.5f;  // Example value, you can adjust this

		// Calculate the impulse magnitude using the impulse formula
		float impulseMagnitude = -(1 + restitution) * relativeVelocityAlongNormal;

		// Calculate the impulse vector
		glm::vec3 impulse = impulseMagnitude * col.normal;
		float totalMass = m_mass + B_physics->GetMass();

		// Apply the impulse to the objects' velocities based on their masses
		if (!isStatic) {
			m_velocity += (impulse / m_mass) * (B_physics->GetMass() / totalMass);
		}

		if (!B_physics->isStatic) {
			B_physics->SetVelocity(B_physics->GetVelocity() - (impulse / B_physics->GetMass()) * (m_mass / totalMass));
		}

		// Adjust the position based on the collision depth
		float penetration = col.depth;  // Collision depth or penetration depth
		float positionCorrectionFactor = 1.0f;  // Example value, you can adjust this

		// Move the objects away from each other along the collision normal
		glm::vec3 positionCorrection = (penetration / totalMass) * positionCorrectionFactor * col.normal;

		if (!isStatic) {
			A_transform->Translate(positionCorrection);
		}

		if (!B_physics->isStatic) {
			B_transform->Translate(-positionCorrection);
		}
	}
}



void PhysicsComponent::Render() {

}
