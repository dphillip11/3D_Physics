#pragma once
#include "GameEngine/Component.h"
#include "GameEngine/TransformComponent.h"

class PhysicsComponent : public Component {
public:
	PhysicsComponent(int GameObjectID, float mass = 1, const glm::vec3& gravity = glm::vec3(0, -10, 0));

	float GetMass() const {
		return m_mass;
	}

	glm::vec3 GetGravity() const {
		return m_gravity;
	}

	void SetGravity(const glm::vec3& gravity) {
		m_gravity = gravity;
	}

	glm::vec3 GetVelocity() const {
		return m_velocity;
	}

	void SetVelocity(const glm::vec3& velocity) {
		m_velocity = velocity;
	}

	glm::vec3 GetAcceleration() const {
		return m_acceleration;
	}

	void ApplyForce(const glm::vec3& force) {
		m_totalForce += force;
	}

	void SetAcceleration(const glm::vec3& acceleration) {
		m_acceleration = acceleration;
	}

	void Update(float deltaTime) override;

	void Render() override;

	void SetTransform(TransformComponent* transform) {
		m_transform = transform;
	}

private:
	float m_mass;
	glm::vec3 m_gravity;
	glm::vec3 m_velocity{ glm::vec3(0.0f) };
	glm::vec3 m_acceleration{ glm::vec3(0.0f) };
	glm::vec3 m_totalForce{ glm::vec3(0.0f) };
	TransformComponent* m_transform;
};

