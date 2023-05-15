#pragma once
#include "GameEngine/Component.h"
#include "Shader.h"

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
	ColliderComponent(int objectID) : Component(objectID), size_(glm::vec3(1.0f)), offset_(glm::vec3(0.0f)), colliderType_(ColliderType::Box),
		OBB_shader(Shader("shaders/vertex/point_shader.glsl", "shaders/fragment/point_shader.glsl")) {
		CreateOBBbuffer();
	}

	// Set the size of the collider
	void SetSize(const glm::vec3& size) {
		size_ = size;
	}

	// Get the size of the collider
	glm::vec3 GetSize() const {
		return size_;
	}

	// Set the offset of the collider
	void SetOffset(const glm::vec3& offset) {
		offset_ = offset;
	}

	// Get the offset of the collider
	glm::vec3 GetOffset() const {
		return offset_;
	}

	// Set the collider type
	void SetColliderType(ColliderType colliderType) {
		colliderType_ = colliderType;
	}

	// Get the collider type
	ColliderType GetColliderType() const {
		return colliderType_;
	}

	std::vector<glm::vec3> CalculateOBBCorners() const;


	Bounds CalculateOrientedBoxBounds() const;

	void Render() override;

	void Update(float deltaTime) override {}

	void UpdateOBB();

	void CreateOBBbuffer();

private:
	Shader OBB_shader;
	std::vector< glm::vec3> OBB_vertices;
	unsigned int m_OBB_VBO{ 0 };
	unsigned int m_OBB_VAO{ 0 };
	glm::vec3 size_;
	glm::vec3 offset_;
	ColliderType colliderType_;

};

