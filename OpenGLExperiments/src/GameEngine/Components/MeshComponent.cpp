#include "PCH/pch.h"
#include "GameEngine/MeshComponent.h"
#include "GameEngine/Component.h"
#include "GameEngine/ColliderComponent.h"
#include "GameEngine/DataManager.h"


void MeshComponent::LoadVertices(const std::vector<MeshVertex>& vertices, const std::vector<unsigned int>& indices)
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
	glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(MeshVertex), &vertices[0], GL_STATIC_DRAW);

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

void MeshComponent::Bind() const {
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
}

void MeshComponent::Unbind() const {
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void MeshComponent::Draw(GLenum fillMode) {
	glPolygonMode(GL_FRONT_AND_BACK, fillMode);
	glDrawElements(GL_TRIANGLES, indices_.size(), GL_UNSIGNED_INT, 0);
}
