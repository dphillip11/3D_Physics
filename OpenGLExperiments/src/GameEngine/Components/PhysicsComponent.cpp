#include "PCH/pch.h"
#include "GameEngine/PhysicsComponent.h"
#include "GameEngine/DataManager.h"
#include "GameEngine/Quaternion.h"
#include "GameEngine/PrimitiveRenderer.h"


PhysicsComponent::PhysicsComponent(int GameObjectID, float mass, const glm::vec3& gravity)
	: m_mass(mass), m_gravity(gravity), m_velocity(0.0f), m_acceleration(0.0f), Component(GameObjectID),
	m_transform(DM.GetComponent<TransformComponent>(GameObjectID)) {}

void PhysicsComponent::Update(float deltaTime) {


	if (!isStatic)
	{
		float damping = 0.995f;

		// Apply gravity to the acceleration
		m_acceleration += m_gravity;

		// Apply the total force to the acceleration
		m_acceleration += m_totalForce / m_mass;

		// Update velocity based on acceleration and time
		m_velocity *= damping;
		m_velocity += m_acceleration * deltaTime;

		// Update position based on velocity and time
		glm::vec3 displacement = m_velocity * deltaTime;
		m_transform->Translate(displacement);

		// Update angular velocity based on torque and time
		m_angularAcceleration = Quaternion::ScaleQuaternion(m_torque, 1 / m_mass) * m_angularAcceleration;
		m_angularVelocity = (damping * m_angularVelocity) + (0.5f * m_angularAcceleration * deltaTime);
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


glm::vec3 CalculateTorque(const glm::vec3& contactPoint, const glm::vec3& centerOfMass, const glm::mat3& inertiaTensor, const glm::vec3& impulse) {
	// Calculate the vector from the center of mass to the contact point
	glm::vec3 r = contactPoint - centerOfMass;

	// Calculate the torque at the contact point
	glm::vec3 torque = glm::cross(r, impulse);

	// Transform the torque into the local space of the object
	torque = glm::transpose(inertiaTensor) * torque;

	return torque;
}

void PhysicsComponent::ApplyTorqueAtContactPoints(PhysicsComponent* rb, const std::vector<glm::vec3>& contactPoints, const glm::vec3& axis, int color) {
	auto center = CollisionManager::GetColliderTransform(rb->gameObjectID)->GetWorldPosition();
	auto angularVelocity = glm::eulerAngles(rb->GetAngularVelocity());
	auto velocity = rb->GetVelocity();
	glm::mat3 inertiaTensor = rb->GetInertiaTensor();

	glm::vec3 totalTorque(0.0f); // Initialize total torque as zero vector

	for (const auto& contactPoint : contactPoints) {
		glm::vec3 pointVelocity = velocity + glm::cross(angularVelocity, contactPoint - center);
		glm::vec3 speedAlongAxis = glm::dot(pointVelocity, -axis) * -axis;
		// Calculate the torque at the contact point
		glm::vec3 torque = CalculateTorque(contactPoint, center, inertiaTensor, speedAlongAxis);
		PrimitiveRenderer::Get().DrawLines(std::vector<glm::vec3>({ contactPoint, contactPoint + torque }), color);
		//PrimitiveRenderer::Get().DrawLines(std::vector<glm::vec3>({ contactPoint, center }), color);
		// Accumulate the torque
		totalTorque += torque;
	}

	if (!contactPoints.empty()) {
		totalTorque /= static_cast<float>(contactPoints.size());
		// Apply the accumulated torque
		rb->ApplyTorque(totalTorque);
	}
}


void PhysicsComponent::ResolveCollisions() {
	while (!m_collisionLog.empty()) {
		collision col = m_collisionLog.front();
		m_collisionLog.pop();
		auto B_physics = DM.GetComponent<PhysicsComponent>(col.ID2);
		auto A_transform = DM.GetComponent<TransformComponent>(col.ID1);
		auto A_colliderPos = CollisionManager::GetColliderTransform(col.ID1)->GetWorldPosition();
		auto B_transform = DM.GetComponent<TransformComponent>(col.ID2);
		auto B_colliderPos = CollisionManager::GetColliderTransform(col.ID2)->GetWorldPosition();

		// Calculate the relative velocity of the two colliding objects
		glm::vec3 relativeVelocity = m_velocity - B_physics->m_velocity;
		float collisionSpeed = glm::dot(relativeVelocity, col.normal);


		auto friction = CalculateFriction(relativeVelocity, col.normal, 0.7f);

		// Define elasticity
		float elasticity = 1.0f;

		// Calculate the impulse
		glm::vec3 impulseVector = -(1 + elasticity) * col.normal * collisionSpeed / (m_mass + B_physics->m_mass);

		//PrimitiveRenderer::Get().DrawPoints(col.contacts);
		//Calculate angular impules
		ApplyTorqueAtContactPoints(this, col.contacts, col.normal, 3);
		ApplyTorqueAtContactPoints(B_physics, col.contacts, col.normal);

		glm::vec3 positionCorrection = (col.depth) * col.normal;

		if (!isStatic && !B_physics->isStatic) {
			A_transform->Translate(-0.5f * positionCorrection);
			B_transform->Translate(0.5f * positionCorrection);
			m_velocity += impulseVector * B_physics->m_mass;
			B_physics->m_velocity -= impulseVector * m_mass;
		}
		else if (!isStatic)
		{
			A_transform->Translate(-positionCorrection);
			m_velocity += impulseVector * (m_mass + B_physics->m_mass);

		}
		else if (!B_physics->isStatic)
		{
			B_transform->Translate(positionCorrection);
			B_physics->m_velocity -= impulseVector * (m_mass + B_physics->m_mass);
		}
	}


}

glm::vec3 PhysicsComponent::CalculateFriction(const glm::vec3& relativeVelocity, const glm::vec3& normal, const float& coefficient) {
	// Calculate the magnitude of the frictional force
	float frictionMagnitude = glm::length(relativeVelocity) * coefficient;

	// Calculate the direction of the frictional force
	glm::vec3 frictionDirection = glm::normalize(-relativeVelocity);

	// Calculate the frictional force vector
	glm::vec3 frictionForce = frictionMagnitude * frictionDirection;

	// Return the frictional force vector
	return frictionForce;
}


void PhysicsComponent::Render() {

}
