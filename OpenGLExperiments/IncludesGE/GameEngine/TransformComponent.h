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

	void SetPosition(const glm::vec3& position) {
		m_transformMatrix[3] = glm::vec4(position, 1.0f);
	}

	void SetRotation(const glm::vec3& rotation) {
		m_transformMatrix = glm::rotate(m_transformMatrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		m_transformMatrix = glm::rotate(m_transformMatrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		m_transformMatrix = glm::rotate(m_transformMatrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	}

	void SetScale(const glm::vec3& scale) {
		m_transformMatrix = glm::scale(m_transformMatrix, scale);
	}

	void Translate(const glm::vec3& translation) {
		m_transformMatrix = glm::translate(m_transformMatrix, translation);
	}

	void Rotate(const glm::vec3& eulerAngles) {
		m_transformMatrix = glm::rotate(m_transformMatrix, glm::radians(eulerAngles.x), glm::vec3(1.0f, 0.0f, 0.0f));
		m_transformMatrix = glm::rotate(m_transformMatrix, glm::radians(eulerAngles.y), glm::vec3(0.0f, 1.0f, 0.0f));
		m_transformMatrix = glm::rotate(m_transformMatrix, glm::radians(eulerAngles.z), glm::vec3(0.0f, 0.0f, 1.0f));
	}

	void Scale(const glm::vec3& scale) {
		m_transformMatrix = glm::scale(m_transformMatrix, scale);
	}

	void Transform(const glm::vec3& translation, const glm::vec3& rotation, const glm::vec3& scale) {
		glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), translation);
		glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
		glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), scale);

		m_transformMatrix = translationMatrix * rotationMatrix * scaleMatrix;
	}


	void Update(float deltaTime) override {
		if (UI_translation != glm::vec3(0))
		{
			Translate(UI_translation);
			UI_translation = glm::vec3(0);
		}
		if (UI_rotation != glm::vec3(0))
		{
			Rotate(UI_rotation);
			UI_rotation = glm::vec3(0);
		}
		if (UI_scale != glm::vec3(0))
		{
			Scale(0.1f * UI_scale + glm::vec3(1));
			UI_scale = glm::vec3(0);
		}
	}

	void Render() override;

	void RenderColliderTransform();

	void SetParent(TransformComponent* parent);

	glm::mat4 GetWorldTransform() const {
		glm::mat4 worldModelMatrix = GetLocalTransform();
		if (m_parent) {
			worldModelMatrix = m_parent->GetWorldTransform() * worldModelMatrix;
		}
		return worldModelMatrix;
	}

	TransformComponent* GetParent() const {
		return m_parent;
	}
private:

	TransformComponent* m_parent{ nullptr };
	glm::mat4 m_transformMatrix{ glm::mat4(1) };

	glm::vec3 UI_translation{ glm::vec3(0) };
	glm::vec3 UI_rotation{ glm::vec3(0) };
	glm::vec3 UI_scale{ glm::vec3(0) };

};