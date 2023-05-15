#pragma once
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include "Component.h"

class TransformComponent :public Component {
public:
	TransformComponent(int gameobjectID, const glm::vec3& position = glm::vec3(0), const glm::vec3& scale = glm::vec3(1), const glm::vec3& rotation = glm::vec3(0)) :
		Component(gameobjectID), position_(position), scale_(scale), rotation_(rotation) {};

	const glm::vec3& GetPosition() const { return position_; }
	void SetPosition(const glm::vec3& position) { position_ = position; }

	const glm::vec3& GetRotation() const { return rotation_; }
	void SetRotation(const glm::vec3& rotation) { rotation_ = rotation; }

	const glm::vec3& GetScale() const { return scale_; }
	void SetScale(const glm::vec3& scale) { scale_ = scale; }

	void Translate(const glm::vec3& translation) {
		position_ += translation;
	}

	glm::mat4 GetTransform() const;

	glm::mat4 GetRotationMatrix() const;

	void Update(float deltaTime) override {}

	void Render() override;


private:
	float privateF{ 0 };
	glm::vec3 position_;
	glm::vec3 rotation_;
	glm::vec3 scale_;
};

