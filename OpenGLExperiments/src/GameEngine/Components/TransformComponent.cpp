#include "PCH/pch.h"
#include "GameEngine/TransformComponent.h"
#include "GameEngine/Component.h"
#include "GameEngine/DataManager.h"

void TransformComponent::Render()
{

}

glm::mat4 TransformComponent::GetLocalTransform() const {
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), m_translation);
	glm::mat4 rotationMatrix = glm::mat4_cast(m_rotation);
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), m_scale);
	return translationMatrix * rotationMatrix * scaleMatrix;
}

glm::mat4 TransformComponent::GetWorldTransform() const {
	glm::mat4 worldModelMatrix = GetLocalTransform();
	if (m_parent) {
		worldModelMatrix = m_parent->GetWorldTransform() * worldModelMatrix;
	}
	return worldModelMatrix;
}

glm::vec3 TransformComponent::GetRotationEulerAngles() {
	return glm::eulerAngles(m_rotation);
}

glm::quat TransformComponent::GetRotationQuat() {
	return m_rotation;
}

glm::vec3 TransformComponent::GetLocalPosition() {
	return m_translation;
}

glm::vec3 TransformComponent::GetWorldPosition() {
	auto translation = m_translation;
	if (m_parent)
	{
		auto parent_transform = m_parent->GetWorldTransform();
		translation = glm::vec3(parent_transform * glm::vec4(translation, 1));
	}
	return translation;
}

glm::vec3 TransformComponent::GetScale()
{
	return m_scale;
}

void TransformComponent::Rotate(glm::vec3 eulerAngles) {
	// Create a quaternion from the given Euler angles
	glm::quat rotationDelta = glm::quat(eulerAngles);

	// Apply the rotation to the existing rotation quaternion
	m_rotation = rotationDelta * m_rotation;

	// Normalize the quaternion to ensure it remains unit length
	m_rotation = glm::normalize(m_rotation);
}

void TransformComponent::Rotate(glm::quat quat) {

	m_rotation = quat * m_rotation;
	// Normalize the quaternion to ensure it remains unit length
	m_rotation = glm::normalize(m_rotation);
}

void TransformComponent::Translate(glm::vec3 translation) {
	m_translation += translation;
}

void TransformComponent::Scale(glm::vec3 scale) {
	m_scale *= scale;
}

void TransformComponent::SetParent(TransformComponent* parent)
{
	if (parent != m_parent && parent != this)
	{

		// Set the new parent
		m_parent = parent;

		// Calculate the new local transform based on the parent's world transform and the stored position, size, and rotation
		if (parent)
		{
			m_translation -= parent->GetWorldPosition();
			m_rotation = glm::normalize(glm::conjugate(parent->m_rotation) * m_rotation * parent->m_rotation);
			m_scale /= parent->m_scale;
		}
	}
}

void TransformComponent::SetLocalPosition(const glm::vec3& position) {
	m_translation = position;
}

void TransformComponent::SetLocalRotation(const glm::vec3& eulerAngles) {
	m_rotation = glm::quat(eulerAngles);
}

void TransformComponent::SetLocalRotation(const glm::quat& quat) {
	m_rotation = quat;
}

void TransformComponent::SetLocalScale(const glm::vec3& scale) {
	m_scale = scale;
}


//glm::vec3 TransformComponent::GetWorldPosition() const
//{
//	glm::vec4 localPosition = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
//	glm::mat4 worldTransform = GetWorldTransform();
//
//	// Multiply the local position by the world transform to get the world position
//	glm::vec4 worldPosition = worldTransform * localPosition;
//
//	return glm::vec3(worldPosition);
//}





