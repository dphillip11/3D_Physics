#include "PCH/pch.h"
#include "GameEngine/RendererComponent.h"
#include "GameEngine/ShaderComponent.h"
#include "GameEngine/MeshComponent.h"
#include "GameEngine/TransformComponent.h"
#include "GameEngine/DataManager.h"
#include "Camera.h"
#include "material.h"

void RendererComponent::Render()
{
	auto shader = DM.GetComponent<ShaderComponent>(gameObjectID);
	auto transform = DM.GetComponent<TransformComponent>(gameObjectID);
	auto mesh = DM.GetComponent<MeshComponent>(gameObjectID);

	if (shader != nullptr && transform != nullptr && mesh != nullptr)
	{
		Light light1{ glm::vec3(0,100,-500), glm::vec3(1), glm::vec3(1), glm::vec3(1) };
		Material mat1{ glm::vec3(0.2f), glm::vec3(0.7f), glm::vec3(0.4f), 32 };
		shader->Use();
		shader->setVec3("viewPosition", Camera::currentCamera->_position);
		shader->m_shader.setLight(light1);
		shader->m_shader.setMaterial(mat1);
		shader->SetViewPosAuto();
		shader->SetModelMatrix(transform->GetWorldTransform());
		mesh->Draw();
		shader->Unuse();
	}
}
