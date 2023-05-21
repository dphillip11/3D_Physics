#include "PCH/pch.h"
#include "GameEngine/TransformComponent.h"
#include "GameEngine/Component.h"
#include "GameEngine/DataManager.h"


void TransformComponent::Render()
{

}

glm::mat4 TransformComponent::GetLocalTransform() const {
	return m_transformMatrix;
}

void TransformComponent::SetParent(TransformComponent* parent)
{
	if (parent != m_parent && parent != this)
	{
		glm::mat4 previousTransform = GetWorldTransform();

		// Set the new parent
		m_parent = parent;

		// Calculate the new local transform based on the parent's world transform and the stored position, size, and rotation
		if (parent)
		{
			glm::mat4 parentWorldTransform = parent->GetWorldTransform();
			glm::mat4 parentWorldTransformInverse = glm::inverse(parentWorldTransform);
			m_transformMatrix = parentWorldTransformInverse;
		}
	}
}

void TransformComponent::SetLocalPosition(const glm::vec3& position) {
	m_transformMatrix[3] = glm::vec4(position, 1.0f);
}

void TransformComponent::SetLocalRotation(const glm::vec3& rotation) {
	m_transformMatrix = glm::rotate(m_transformMatrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	m_transformMatrix = glm::rotate(m_transformMatrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	m_transformMatrix = glm::rotate(m_transformMatrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
}

void TransformComponent::SetLocalScale(const glm::vec3& scale) {
	m_transformMatrix = glm::scale(m_transformMatrix, scale);
}

void TransformComponent::Translate_Local(const glm::vec3& translation) {
	m_transformMatrix = glm::translate(m_transformMatrix, translation);
}

void TransformComponent::Rotate_Local(const glm::vec3& eulerAngles) {
	m_transformMatrix = glm::rotate(m_transformMatrix, glm::radians(eulerAngles.x), glm::vec3(1.0f, 0.0f, 0.0f));
	m_transformMatrix = glm::rotate(m_transformMatrix, glm::radians(eulerAngles.y), glm::vec3(0.0f, 1.0f, 0.0f));
	m_transformMatrix = glm::rotate(m_transformMatrix, glm::radians(eulerAngles.z), glm::vec3(0.0f, 0.0f, 1.0f));
}

void TransformComponent::Scale_Local(const glm::vec3& scale) {
	glm::vec3 local_position = glm::vec3(m_transformMatrix * glm::vec4(0, 0, 0, 1));
	Translate_Local(-local_position);
	m_transformMatrix = glm::scale(m_transformMatrix, scale);
	Translate_Local(local_position);
}

void TransformComponent::Transform_Local(const glm::vec3& translation, const glm::vec3& rotation, const glm::vec3& scale) {
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), translation);
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), scale);

	m_transformMatrix = translationMatrix * rotationMatrix * scaleMatrix;
}

glm::mat4 TransformComponent::GetWorldTransform() const {
	glm::mat4 worldModelMatrix = GetLocalTransform();
	if (m_parent) {
		worldModelMatrix = m_parent->GetWorldTransform() * worldModelMatrix;
	}
	return worldModelMatrix;
}

glm::vec3 TransformComponent::GetWorldPosition() const
{
	glm::vec4 localPosition = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	glm::mat4 worldTransform = GetWorldTransform();

	// Multiply the local position by the world transform to get the world position
	glm::vec4 worldPosition = worldTransform * localPosition;

	return glm::vec3(worldPosition);
}

glm::vec3 TransformComponent::GetWorldRotation() const
{
	glm::mat4 worldTransform = GetWorldTransform();
	glm::quat worldRotation = glm::quat_cast(worldTransform);
	return glm::eulerAngles(worldRotation);
}

glm::vec3 TransformComponent::GetWorldScale() const
{
	glm::mat4 worldTransform = GetWorldTransform();
	glm::vec3 worldScale;
	worldScale.x = glm::length(glm::vec3(worldTransform[0]));
	worldScale.y = glm::length(glm::vec3(worldTransform[1]));
	worldScale.z = glm::length(glm::vec3(worldTransform[2]));
	return worldScale;
}

void TransformComponent::Translate_World(glm::vec3 translation)
{
	// Get the current world position
	glm::vec3 worldPosition = GetWorldPosition();

	// Apply the translation to the world position
	glm::vec3 newWorldPosition = worldPosition + translation;

	glm::vec3 localTranslation;
	// Calculate the translation in local space
	if (m_parent)
		localTranslation = glm::inverse(m_parent->GetWorldTransform()) * glm::vec4(newWorldPosition, 1.0f);
	else
		localTranslation = newWorldPosition;

	// Update the local transform
	SetLocalPosition(localTranslation);
}



