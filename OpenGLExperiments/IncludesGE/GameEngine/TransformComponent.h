#pragma once
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include "Component.h"

class TransformComponent :public Component {
public:
	TransformComponent(int ObjectID = -1, TransformComponent* parent = nullptr) :
		Component(ObjectID) {
		if (parent)
			SetParent(parent);
	}

	glm::mat4 GetLocalTransform() const;
	glm::mat4 GetWorldTransform() const;

	glm::vec3 GetRotationEulerAngles();
	glm::quat GetRotationQuat();
	glm::vec3 GetLocalPosition();
	glm::vec3 GetWorldPosition();
	glm::vec3 GetScale();

	void SetLocalPosition(const glm::vec3& position);
	void SetLocalRotation(const glm::vec3& eulerAngles);
	void SetLocalRotation(const glm::quat& quat);
	void SetLocalScale(const glm::vec3& scale);

	void Rotate(glm::vec3 eulerAngles);
	void Rotate(glm::quat quat);
	void Translate(glm::vec3 translation);
	void Scale(glm::vec3 scale);

	void Update(float deltaTime) override {}

	void Render() override;

	void SetParent(TransformComponent* parent);

	TransformComponent* GetParent() const {
		return m_parent;
	}


private:

	TransformComponent* m_parent{ nullptr };
	glm::vec3 m_translation = glm::vec3(0);
	glm::quat m_rotation = glm::identity<glm::quat>();
	glm::vec3 m_scale = glm::vec3(1);

};