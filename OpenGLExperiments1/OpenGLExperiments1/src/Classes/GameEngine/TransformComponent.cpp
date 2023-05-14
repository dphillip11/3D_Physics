#include "pch.h"
#include "TransformComponent.h"
#include "Component.h"


void TransformComponent::Render()
{
	ImGui::Text("Transform Component");
	ImGui::DragFloat3("Position: ", &position_.x);
	ImGui::DragFloat3("Scale: ", &scale_.x);
	ImGui::DragFloat3("Rotation: ", &rotation_.x);
}

