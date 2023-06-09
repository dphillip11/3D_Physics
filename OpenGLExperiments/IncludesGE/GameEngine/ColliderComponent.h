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

	ColliderComponent(int objectID, bool isSphere = false);

	TransformComponent& m_collider_transform;

	// Set the collider type
	void SetColliderType(ColliderType colliderType) {
		colliderType_ = colliderType;
	}

	// Get the collider type
	ColliderType GetColliderType() const {
		return colliderType_;
	}

	void CalculateOBBCorners(std::vector<glm::vec3>&) const;

	// returns {min:{x,y,z},max:{x,y,z}}, store as necessary
	Bounds CalculateAABB() const;

	void Render() override;

	void Update(float deltaTime) override {
		m_collider_transform.Update(deltaTime);
	}

	void UpdateOBB();

	void CreateOBBbuffer();

	void ToggleCollider()
	{
		showBoxCollider = !showBoxCollider;
	}

private:
	bool showBoxCollider = false;
	Shader& OBB_shader;
	Mesh& OBB_Mesh;
	ColliderType colliderType_;
};

