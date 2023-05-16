#include "PCH/pch.h"
#include "GameEngine/RendererComponent.h"
#include "GameEngine/ShaderComponent.h"
#include "GameEngine/MeshComponent.h"
#include "GameEngine/TransformComponent.h"
#include "GameEngine/DataManager.h"

void RendererComponent::Render()
{
	auto shader = DM.GetComponent<ShaderComponent>(gameObjectID);
	auto transform = DM.GetComponent<TransformComponent>(gameObjectID);
	auto mesh = DM.GetComponent<MeshComponent>(gameObjectID);

	if (shader != nullptr && transform != nullptr && mesh != nullptr)
	{
		shader->Use();
		shader->SetViewPosAuto();
		shader->SetModelMatrix(transform->GetTransform());
		mesh->Draw();
		shader->Unuse();
	}
}
