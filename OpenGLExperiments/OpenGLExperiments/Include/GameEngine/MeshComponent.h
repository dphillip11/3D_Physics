#pragma once
#include "Component.h"

struct MeshVertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texcoord;
};

class MeshComponent : public Component {
public:
	MeshComponent(GameObject* gameobject) : Component(gameobject) {};

	void LoadVertices(const std::vector<MeshVertex>& vertices, const std::vector<unsigned int>& indices)
	{
		vertices_ = vertices;
		indices_ = indices;

		// Generate the VAO, VBO, and EBO
		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);
		glGenBuffers(1, &m_EBO);

		// Bind the VAO
		glBindVertexArray(m_VAO);

		// Bind and set up the VBO
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(MeshVertex), &vertices_[0], GL_STATIC_DRAW);

		// Bind and set up the EBO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_.size() * sizeof(unsigned int), &indices_[0], GL_STATIC_DRAW);

		// Set up the vertex attribute pointers
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)offsetof(MeshVertex, position));
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)offsetof(MeshVertex, normal));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)offsetof(MeshVertex, texcoord));
		glEnableVertexAttribArray(2);

		// Unbind the VAO, VBO, and EBO
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	const std::vector<MeshVertex>& GetVertices() const { return vertices_; }
	const std::vector<unsigned int>& GetIndices() const { return indices_; }

	void Bind() const {
		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	}

	void Unbind() const {
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void Draw(GLenum fillMode = GL_FILL) {
		glPolygonMode(GL_FRONT_AND_BACK, fillMode);
		glDrawElements(GL_TRIANGLES, indices_.size(), GL_UNSIGNED_INT, 0);
	}

	void Update(float deltaTime) override
	{

	}

	void Render() override
	{

	}

private:
	unsigned int m_VAO{ 0 };
	unsigned int m_VBO{ 0 };
	unsigned int m_EBO{ 0 };

	std::vector<MeshVertex> vertices_;
	std::vector<unsigned int> indices_;
};
