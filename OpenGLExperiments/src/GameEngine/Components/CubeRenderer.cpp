#include "PCH/pch.h"
#include "Camera.h"
#include "GameEngine/CubeRenderer.h"
#include "GameEngine/DataManager.h"
#include "GameEngine/MeshComponent.h"
#include "GameEngine/ShaderComponent.h"
#include "GameEngine/TransformComponent.h"

struct CubeRenderer::Impl {
public:
	MeshComponent* m_Mesh;
	ShaderComponent* m_Shader;
};

CubeRenderer::CubeRenderer(int gameobjectID) : RendererComponent(gameobjectID)
{

	const std::vector<unsigned int> indices = {
		// Front face
		0, 1, 2,
		2, 3, 0,
		// Back face
		4, 5, 6,
		6, 7, 4,
		// Left face
		8, 9, 10,
		10, 11, 8,
		// Right face
		12, 13, 14,
		14, 15, 12,
		// Top face
		16, 17, 18,
		17, 18, 19,
		// Bottom face
		20, 21, 22,
		20, 22, 23
	};

	const std::vector<MeshVertex> vertices{
		// Front face
		{ {-0.5f, -0.5f, 0.5f}, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f }},
		{ { 0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f} },
		{ { 0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f} },
		{ {-0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f} },
		// Back face
		{ {-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f} },
		{ { 0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f} },
		{ { 0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f} },
		{ {-0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f} },
		// Left face
		{ {-0.5f,  0.5f,  0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f} },
		{ {-0.5f,  0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f} },
		{ {-0.5f, -0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f} },
		{ {-0.5f, -0.5f,  0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f} },
		// Right face
		{ {0.5f,  0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f} },
		{ {0.5f,  0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f} },
		{ {0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f} },
		{ {0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f} },
		// Top face
		{ { 0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f} },
		{ {-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f} },
		{ { 0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f} },
		{ {-0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f} },
		// Bottom face
		{ {-0.5f, -0.5f, 0.5f}, { 0.0f, -1.0f, 0.0f }, { 0.0f, 0.0f }},
		{ { 0.5f, -0.5f,  0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f} },
		{ { 0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f} },
		{ {-0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f} }
	};

	_impl = std::make_unique<Impl>();
	_impl->m_Mesh = DM.AddComponent<MeshComponent>(gameObjectID);
	_impl->m_Mesh->LoadVertices(vertices, indices);
	_impl->m_Shader = DM.AddComponent<ShaderComponent>(gameObjectID);
	_impl->m_Shader->Setup("Shaders/vertex/mesh_vShader.glsl", "Shaders/fragment/mesh_fShader.glsl");
}


void CubeRenderer::Render()
{
	_impl->m_Shader->Use();

	auto transformComponent = DM.GetComponent<TransformComponent>(gameObjectID);
	if (transformComponent) {
		_impl->m_Shader->SetModelMatrix(transformComponent->GetTransform());
	}
	else {
		_impl->m_Shader->SetModelMatrix(glm::mat4(1));
	}

	_impl->m_Shader->SetProjectionMatrix(Camera::currentCamera->projection);
	_impl->m_Shader->SetViewMatrix(Camera::currentCamera->view());

	_impl->m_Mesh->Bind();
	_impl->m_Mesh->Draw();

	_impl->m_Mesh->Unbind();
	_impl->m_Shader->Unuse();
}

