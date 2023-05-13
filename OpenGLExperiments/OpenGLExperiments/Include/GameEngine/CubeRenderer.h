#include "RendererComponent.h"
#include "MeshComponent.h"
#include "ShaderComponent.h"
#include "TransformComponent.h"


class CubeRenderer : public RendererComponent
{
public:
	CubeRenderer(GameObject* gameobject) : RendererComponent(gameobject)
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

		std::vector<MeshVertex> vertices{
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

		DM::addComponent(gameObjectID, DM::MeshComponents);
		DM::MeshComponents[gameObjectID]->LoadVertices(vertices, indices);
		DM::addComponent(gameObjectID, DM::ShaderComponents);
		m_Shader = std::make_unique<ShaderComponent>(gameObject_);
		m_Shader->Setup("Shaders/vertex/mesh_vShader.glsl", "Shaders/fragment/mesh_fShader.glsl");
	}

	virtual void Update(float deltaTime) override
	{

	}

	virtual void Render() override
	{
		m_Shader->Use();

		auto transformComponent = gameObject_->GetComponent<TransformComponent>();
		if (transformComponent) {
			m_Shader->SetModelMatrix(transformComponent->GetTransform());
		}
		else {
			m_Shader->SetModelMatrix(glm::mat4(1));
		}

		m_Shader->SetProjectionMatrix(Camera::currentCamera->projection);
		m_Shader->SetViewMatrix(Camera::currentCamera->view());

		m_Mesh->Bind();
		m_Mesh->Draw();
		m_Mesh->Draw(GL_LINE);

		m_Mesh->Unbind();
		m_Shader->Unuse();
	}

private:
	std::unique_ptr<MeshComponent> m_Mesh;
	std::unique_ptr <ShaderComponent> m_Shader;
};
