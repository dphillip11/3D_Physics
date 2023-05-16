#include "PCH/pch.h"
#include "GameEngine/TransformComponent.h"
#include "GameEngine/Component.h"
#include "GameEngine/DataManager.h"


void TransformComponent::Render()
{
	if (ImGui::Button("Parent"))
		SetParent(DM.GetComponent<TransformComponent>(1));
	ImGui::DragFloat3(&("Position: " + std::to_string(gameObjectID))[0], &position_.x);
	ImGui::DragFloat3(&("Scale: " + std::to_string(gameObjectID))[0], &scale_.x);
	ImGui::DragFloat3(&("Rotation: " + std::to_string(gameObjectID))[0], &rotation_.x);
}

glm::mat4 TransformComponent::GetLocalTransform() const {
	glm::mat4 transform = glm::mat4(1.0f);
	transform = glm::translate(transform, position_);
	transform = glm::rotate(transform, glm::radians(rotation_.x), glm::vec3(1.0f, 0.0f, 0.0f));
	transform = glm::rotate(transform, glm::radians(rotation_.y), glm::vec3(0.0f, 1.0f, 0.0f));
	transform = glm::rotate(transform, glm::radians(rotation_.z), glm::vec3(0.0f, 0.0f, 1.0f));
	transform = glm::scale(transform, scale_);
	return transform;
}

glm::mat4 TransformComponent::GetRotationMatrix() const {
	glm::quat rotationQuat = glm::quat(rotation_);

	// Convert the quaternion to a rotation matrix
	glm::mat4 rotationMatrix = glm::mat4_cast(rotationQuat);

	return rotationMatrix;
}

