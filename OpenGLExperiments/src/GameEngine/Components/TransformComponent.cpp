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


