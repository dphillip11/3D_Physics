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



ColliderComponent::ColliderComponent(int objectID, bool isSphere)
	: Component(objectID),
	colliderType_(isSphere ? ColliderType::Sphere : ColliderType::Box),
	OBB_shader(ShaderManager::GetInstance().LoadShader(GetFilePath(Shaders::Basic))),
	OBB_Mesh(MeshManager::GetInstance().LoadMesh(GetFilePath(isSphere ? Models::Sphere : Models::Cube))),
	m_collider_transform(CollisionManager::AddColliderTransform(objectID))
{
	m_collider_transform.SetParent(DM.GetComponent<TransformComponent>(objectID));
	auto mesh = DM.GetComponent<MeshComponent>(objectID);
	if (mesh != nullptr)
	{
		auto pos = mesh->m_mesh.upper_bounds + mesh->m_mesh.lower_bounds;
		auto scale = mesh->m_mesh.upper_bounds - mesh->m_mesh.lower_bounds;
		scale = isSphere ? scale * 0.5f : scale;
		//scale collider to fit object
		m_collider_transform.Scale(scale);
		m_collider_transform.Translate(0.5f * (pos));
		auto transform = DM.GetComponent<TransformComponent>(objectID);
		if (transform)
		{
			//scale object and move to centre of scene
			transform->Scale(glm::vec3(5.0f / scale.y));
			transform->Translate(-0.5f * (5 / scale.y) * (mesh->m_mesh.upper_bounds + mesh->m_mesh.lower_bounds));
		}
	}
}

void ColliderComponent::CalculateOBBCorners(std::vector<glm::vec3>& corners) const {
	glm::mat4 modelMatrix = m_collider_transform.GetWorldTransform();

	// Calculate the corners of the collider

	corners.push_back(glm::vec3(modelMatrix * 0.5f * glm::vec4(-1, 1, 1, 2)));
	corners.push_back(glm::vec3(modelMatrix * 0.5f * glm::vec4(1, -1, 1, 2)));
	corners.push_back(glm::vec3(modelMatrix * 0.5f * glm::vec4(1, 1, -1, 2)));
	corners.push_back(glm::vec3(modelMatrix * 0.5f * glm::vec4(1, 1, 1, 2)));
	corners.push_back(glm::vec3(modelMatrix * 0.5f * glm::vec4(-1, -1, 1, 2)));
	corners.push_back(glm::vec3(modelMatrix * 0.5f * glm::vec4(-1, 1, -1, 2)));
	corners.push_back(glm::vec3(modelMatrix * 0.5f * glm::vec4(1, -1, -1, 2)));
	corners.push_back(glm::vec3(modelMatrix * 0.5f * glm::vec4(-1, -1, -1, 2)));

}


Bounds ColliderComponent::CalculateAABB() const {
	// Get the corners of the cube collider
	std::vector<glm::vec3> corners;
	CalculateOBBCorners(corners);

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
	if (showBoxCollider)
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


