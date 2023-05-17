#include "PCH/pch.h"
#include "GameEngine/TransformComponent.h"
#include "GameEngine/Component.h"
#include "GameEngine/DataManager.h"


void TransformComponent::Render()
{
	ImGui::PushID(gameObjectID);
	if (ImGui::Button("Parent"))
		SetParent(DM.GetComponent<TransformComponent>(1));
	ImGui::DragFloat3("Position: ", &position_.x);
	ImGui::DragFloat3("Scale: ", &scale_.x);
	ImGui::DragFloat3("Rotation: ", &rotation_.x);
	ImGui::PopID();
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

void TransformComponent::SetParent(TransformComponent* new_parent)
{
	if (new_parent != parent && new_parent != this)
	{
		// Store the child's current local transform
		glm::mat4 previousLocalTransform = GetLocalTransform();

		// Set the new parent
		parent = new_parent;

		// Calculate the new local transform based on the parent's world transform and the stored local transform
		if (parent)
		{
			glm::mat4 parentWorldTransform = parent->GetWorldTransform();
			glm::mat4 parentWorldTransformInverse = glm::inverse(parentWorldTransform);
			localTransform_ = parentWorldTransformInverse * previousLocalTransform;
		}
		else
		{
			// If no parent is set, the local transform becomes the world transform
			localTransform_ = previousLocalTransform;
		}
	}
}

