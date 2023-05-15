#include "PCH/pch.h"
#include "GameEngine/TransformComponent.h"
#include "GameEngine/Component.h"


void TransformComponent::Render()
{
	ImGui::Text("Transform Component");
	ImGui::DragFloat3("Position: ", &position_.x);
	ImGui::DragFloat3("Scale: ", &scale_.x);
	ImGui::DragFloat3("Rotation: ", &rotation_.x);
}

glm::mat4 TransformComponent::GetTransform() const {
	glm::mat4 transform = glm::mat4(1.0f);
	transform = glm::translate(transform, position_);
	transform = glm::rotate(transform, glm::radians(rotation_.x), glm::vec3(1.0f, 0.0f, 0.0f));
	transform = glm::rotate(transform, glm::radians(rotation_.y), glm::vec3(0.0f, 1.0f, 0.0f));
	transform = glm::rotate(transform, glm::radians(rotation_.z), glm::vec3(0.0f, 0.0f, 1.0f));
	transform = glm::scale(transform, scale_);
	return transform;
}

