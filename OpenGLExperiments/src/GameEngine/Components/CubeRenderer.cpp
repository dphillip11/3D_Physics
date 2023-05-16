#include "PCH/pch.h"
#include "GameEngine/CubeRenderer.h"
#include "GameEngine/DataManager.h"
#include "GameEngine/MeshComponent.h"
#include "GameEngine/ShaderComponent.h"
#include "GameEngine/TransformComponent.h"

struct CubeRenderer::Impl {
	MeshComponent* m_Mesh;
	ShaderComponent* m_Shader;
};

CubeRenderer::CubeRenderer(int gameobjectID) : RendererComponent(gameobjectID)
{
	_impl = std::make_unique<Impl>();
	_impl->m_Mesh = DM.AddComponent<MeshComponent>(gameObjectID, "Assets/cube.obj");
	_impl->m_Shader = DM.AddComponent<ShaderComponent>(gameObjectID, "Shaders/Combined/Basic.hlsl");
}



