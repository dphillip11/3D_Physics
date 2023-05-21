#pragma once
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include "Component.h"

class TransformComponent :public Component {
public:
	TransformComponent(int ObjectID = -1, glm::mat4 model = glm::mat4(1), TransformComponent* parent = nullptr) :
		Component(ObjectID), m_transformMatrix(model) {
		if (parent)
			SetParent(parent);
	}

	glm::mat4 GetLocalTransform() const;

	void SetLocalPosition(const glm::vec3& position);

	void SetLocalRotation(const glm::vec3& rotation);

	void SetLocalScale(const glm::vec3& scale);

	// translate in model space
	void Translate_Local(const glm::vec3& translation);
	// rotate in model space
	void Rotate_Local(const glm::vec3& eulerAngles);
	// scale in model space
	void Rotate(const glm::quat rotation) {
		glm::quat localRotation = glm::quat_cast(m_transformMatrix);
		glm::quat newLocalRotation = rotation * localRotation;
		m_transformMatrix = glm::mat4_cast(newLocalRotation);
	}
	glm::quat ExtractQuaternionRotation() {
		glm::mat3 rotationMatrix = glm::mat3(m_transformMatrix);
		return glm::quat_cast(rotationMatrix);
	}

	void Scale_Local(const glm::vec3& scale);
	// combined transformation in local space
	void Transform_Local(const glm::vec3& translation, const glm::vec3& rotation, const glm::vec3& scale);
	// get transformation matrix from model to world space
	glm::mat4 GetWorldTransform() const;
	// get position in world space
	glm::vec3 GetWorldPosition() const;
	// get rotation in world space
	glm::vec3 GetWorldRotation() const;
	// get scale in world space
	glm::vec3 GetWorldScale() const;
	// translate in world space
	void Translate_World(glm::vec3 translation);

	void Update(float deltaTime) override {

	}

	void Render() override;

	void SetParent(TransformComponent* parent);

	TransformComponent* GetParent() const {
		return m_parent;
	}


private:

	TransformComponent* m_parent{ nullptr };
	glm::mat4 m_transformMatrix{ glm::mat4(1) };

};