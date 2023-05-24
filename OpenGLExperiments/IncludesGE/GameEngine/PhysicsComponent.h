#pragma once
#include "GameEngine/Component.h"
#include "GameEngine/TransformComponent.h"

class PhysicsComponent : public Component {
public:
	PhysicsComponent(int GameObjectID, float mass = 1, const glm::vec3& gravity = glm::vec3(0, -10, 0));

	glm::quat GetTorque() const {
		return m_torque;
	}

	void SetTorque(const glm::quat& torque) {
		m_torque = torque;
	}

	glm::quat GetAngularVelocity() const {
		return m_angularVelocity;
	}

	//set angular velocity euler angles in radians
	void SetAngularVelocity(const glm::vec3& angularVelocity) {
		m_angularVelocity = glm::quat(angularVelocity);
	}

	//set angular velocity euler angles in radians
	void SetAngularVelocity(const glm::quat& angularVelocity) {
		m_angularVelocity = angularVelocity;
	}

	glm::quat GetAngularAcceleration() const {
		return m_angularAcceleration;
	}

	//set using euler angles in radians
	void SetAngularAcceleration(const glm::vec3& angularA) {
		m_angularAcceleration = glm::quat(angularA);
	}

	void SetAngularAcceleration(const glm::quat& angularA) {
		m_angularAcceleration = angularA;
	}

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
		m_totalForce = force + m_totalForce;
	}

	void ApplyTorque(const glm::quat& torque) {
		m_torque = torque * m_torque;
	}

	void ApplyTorque(const glm::vec3& torque) {
		m_torque = glm::quat(torque) * m_torque;
	}

	void SetAcceleration(const glm::vec3& acceleration) {
		m_acceleration = acceleration;
	}

	void Update(float deltaTime) override;

	void Render() override;

	void SetTransform(TransformComponent* transform) {
		m_transform = transform;
	}

	void ToggleStatic()
	{
		isStatic = !isStatic;
	}

	void AddCollision(collision col)
	{
		if (col.valid)
		{
			//std::cout << col.depth << std::endl;
			m_collisionLog.push(col);
		}
	}

	void ResolveCollisions();

private:
	float m_mass = 1;
	bool isStatic = true;
	glm::vec3 m_gravity;

	glm::vec3 m_velocity{ glm::vec3(0.0f) };
	glm::vec3 m_acceleration{ glm::vec3(0.0f) };

	glm::quat m_angularVelocity = glm::identity<glm::quat>();
	glm::quat m_angularAcceleration = glm::identity<glm::quat>();

	glm::quat m_torque = glm::identity<glm::quat>();
	glm::vec3 m_totalForce{ glm::vec3(0.0f) };

	TransformComponent* m_transform;
	std::queue<collision> m_collisionLog;

};

