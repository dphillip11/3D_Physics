#pragma once
#include "GameEngine/Component.h"
#include "GLFW/glfw3.h"

class MeshComponent : public Component {
public:
	MeshComponent(int gameobjectID) : Component(gameobjectID) {};

	void LoadVertices(const std::vector<MeshVertex>& vertices, const std::vector<unsigned int>& indices);

	const std::vector<MeshVertex>& GetVertices() const { return vertices_; }
	const std::vector<unsigned int>& GetIndices() const { return indices_; }

	void Bind() const;

	void Unbind() const;

	void Draw(GLenum fillmode = GL_FILL);

	void Update(float deltaTime) override {}

	void Render() override {}

private:
	unsigned int m_VAO{ 0 };
	unsigned int m_VBO{ 0 };
	unsigned int m_EBO{ 0 };

	std::vector<MeshVertex> vertices_;
	std::vector<unsigned int> indices_;
};
