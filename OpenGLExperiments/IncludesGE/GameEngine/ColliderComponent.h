#pragma once
#include "GameEngine/Component.h"
#include "GameEngine/TransformComponent.h"
#include "Shader.h"
#include "GameENgine/Mesh.h"

enum class ColliderType {
	Box,
	Sphere
};

// contains minimum and maximum boundaries along the x, y and z axes
struct Bounds {
	glm::vec3 min;
	glm::vec3 max;
};


class ColliderComponent : public Component {
public:

	ColliderComponent(int objectID);

	TransformComponent& transform;

	// Set the collider type
	void SetColliderType(ColliderType colliderType) {
		colliderType_ = colliderType;
	}

	// Get the collider type
	ColliderType GetColliderType() const {
		return colliderType_;
	}

	std::vector<glm::vec3> CalculateOBBCorners() const;

	// returns {min:{x,y,z},max:{x,y,z}}, store as necessary
	Bounds CalculateAABB() const;

	void Render() override;

	void Update(float deltaTime) override {}

	void UpdateOBB();

	void CreateOBBbuffer();

private:
	Shader& OBB_shader;
	Mesh& OBB_Mesh;
	std::vector< glm::vec3> OBB_vertices;
	unsigned int m_OBB_VBO{ 0 };
	unsigned int m_OBB_VAO{ 0 };
	glm::vec3 size_;
	glm::vec3 offset_;
	ColliderType colliderType_;

};

