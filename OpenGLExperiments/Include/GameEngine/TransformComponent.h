#pragma once
#include <glm/glm/vec3.hpp>
#include <glm/glm/mat4x4.hpp>
#include "Component.h"

class TransformComponent :public Component {
public:
	TransformComponent(int gameobjectID, const glm::vec3& position = glm::vec3(0), const glm::vec3& rotation = glm::vec3(0), const glm::vec3& scale = glm::vec3(1)) :
		Component(gameobjectID), position_(position), rotation_(rotation), scale_(scale) {};

	const glm::vec3& GetPosition() const { return position_; }
	void SetPosition(const glm::vec3& position) { position_ = position; }

	const glm::vec3& GetRotation() const { return rotation_; }
	void SetRotation(const glm::vec3& rotation) { rotation_ = rotation; }

	const glm::vec3& GetScale() const { return scale_; }
	void SetScale(const glm::vec3& scale) { scale_ = scale; }

	glm::mat4 GetTransform() const;

	void Update(float deltaTime) override
	{

	}

	void Render() override;

private:
	glm::vec3 position_;
	glm::vec3 rotation_;
	glm::vec3 scale_;
};
