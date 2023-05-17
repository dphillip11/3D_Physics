#include "PCH/pch.h"
#include "GameEngine/ColliderComponent.h"
#include "GameEngine/DataManager.h"
#include "GameEngine/MeshManager.h"
#include "GameEngine/TransformComponent.h"
#include "GameEngine/ShaderComponent.h"
#include "GameEngine/ShaderManager.h"
#include "GameEngine/CollisionManager.h"
#include "GameEngine/MeshComponent.h"
#include "Camera.h"
#include "GameEngine/FileManager.h"

ColliderComponent::ColliderComponent(int objectID)
	: Component(objectID),
	colliderType_(ColliderType::Box),
	OBB_shader(ShaderManager::GetInstance().LoadShader(GetFilePath(Shaders::Basic))),
	OBB_Mesh(MeshManager::GetInstance().LoadMesh(GetFilePath(Models::Cube))),
	m_collider_transform(CollisionManager::AddCollider(objectID))
{
	m_collider_transform.SetParent(DM.GetComponent<TransformComponent>(objectID));
}

std::vector<glm::vec3> ColliderComponent::CalculateOBBCorners() const {
	std::vector<glm::vec3> corners(8, glm::vec3(0.0f));

	glm::mat4 modelMatrix = m_collider_transform.GetWorldTransform();

	// Calculate the corners of the collider

	corners[0] = glm::vec3(modelMatrix * glm::vec4(-1, 1, 1, 1));
	corners[1] = glm::vec3(modelMatrix * glm::vec4(1, -1, 1, 1));
	corners[2] = glm::vec3(modelMatrix * glm::vec4(1, 1, -1, 1));
	corners[3] = glm::vec3(modelMatrix * glm::vec4(1, 1, 1, 1));
	corners[4] = glm::vec3(modelMatrix * glm::vec4(-1, -1, 1, 1));
	corners[5] = glm::vec3(modelMatrix * glm::vec4(-1, 1, -1, 1));
	corners[6] = glm::vec3(modelMatrix * glm::vec4(1, -1, -1, 1));
	corners[7] = glm::vec3(modelMatrix * glm::vec4(-1, -1, -1, 1));

	return corners;
}


Bounds ColliderComponent::CalculateAABB() const {
	// Get the corners of the cube collider
	std::vector<glm::vec3> corners = CalculateOBBCorners();

	// Initialize the minimum and maximum bounds with the first corner
	glm::vec3 minBounds = corners[0];
	glm::vec3 maxBounds = corners[0];

	// Find the minimum and maximum bounds by comparing all corners
	for (const glm::vec3& corner : corners) {
		minBounds = glm::min(minBounds, corner);
		maxBounds = glm::max(maxBounds, corner);
	}

	// Create the Bounds structure with the calculated bounds
	Bounds bounds;
	bounds.min = minBounds;
	bounds.max = maxBounds;

	return bounds;
}

void ColliderComponent::Render() {
	m_collider_transform.RenderColliderTransform();
	UpdateOBB();

}

void ColliderComponent::UpdateOBB() {
	auto model = m_collider_transform.GetWorldTransform();
	OBB_shader.Use();
	OBB_shader.setMat4("u_model", model);
	OBB_shader.setMat4("u_view", Camera::currentCamera->view());
	OBB_shader.setMat4("u_projection", Camera::currentCamera->projection);
	OBB_shader.setBool("wireframe", true);
	OBB_Mesh.Bind();
	OBB_Mesh.draw(GL_LINE);
	OBB_shader.setBool("wireframe", false);
	OBB_Mesh.Unbind();
	OBB_shader.Unuse();

}

void ColliderComponent::CreateOBBbuffer()
{
	OBB_vertices = CalculateOBBCorners();
	glGenVertexArrays(1, &m_OBB_VAO);
	glGenBuffers(1, &m_OBB_VBO);

	glBindVertexArray(m_OBB_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_OBB_VBO);
	glBufferData(GL_ARRAY_BUFFER, OBB_vertices.size() * sizeof(glm::vec3), &OBB_vertices[0], GL_STREAM_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


