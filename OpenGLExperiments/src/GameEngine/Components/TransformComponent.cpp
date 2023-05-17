#include "PCH/pch.h"
#include "GameEngine/TransformComponent.h"
#include "GameEngine/Component.h"
#include "GameEngine/DataManager.h"


void TransformComponent::Render()
{
	if (ImGui::CollapsingHeader("Transform"))
	{
		ImGui::SliderFloat3("Translate: ", &UI_translation[0], -0.01, 0.01);
		ImGui::SliderFloat3("Scale: ", &UI_scale[0], -0.01, 0.01);
		ImGui::SliderFloat3("Rotate: ", &UI_rotation[0], -0.1, 0.1);
	}
}

void TransformComponent::RenderColliderTransform()
{
	if (ImGui::CollapsingHeader("Box Collider"))
	{
		ImGui::Text("Translate");
		ImGui::SliderFloat3("##cTranslate", &UI_translation[0], -0.01, 0.01);
		ImGui::Text("Scale");
		ImGui::SliderFloat3("##cScale", &UI_scale[0], -0.01, 0.01);
		ImGui::Text("Rotate");
		ImGui::SliderFloat3("##cRotate", &UI_rotation[0], -0.1, 0.1);
	}
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


