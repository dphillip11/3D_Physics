#include "PCH/pch.h"
#include "Shader.h"
#include "GameEngine/FileManager.h"
#include "GameEngine/PrimitiveRenderer.h"
#include "GameEngine/ShaderManager.h"
#include "Camera.h"


PrimitiveRenderer::PrimitiveRenderer()
{
	m_shader = ShaderManager::GetInstance().LoadShader(GetFilePath(Shaders::PointShader));
}

void PrimitiveRenderer::DrawPoints(const std::vector<glm::vec3>& vertices, int color)
{
	Get()._Draw(vertices, color);
	Get().m_mesh.draw(GL_LINE, GL_POINTS);
	Get().m_shader.Unuse();
}

void PrimitiveRenderer::DrawLines(const std::vector<glm::vec3>& vertices, int color)
{
	Get()._Draw(vertices, color);
	Get().m_mesh.draw(GL_LINE, GL_LINES);
	Get().m_shader.Unuse();
}

void::PrimitiveRenderer::_Draw(const std::vector<glm::vec3>& vertices, int color)
{
	Get().m_shader.Use();
	Get().m_shader.setMat4("u_projection", Camera::currentCamera->projection);
	Get().m_shader.setMat4("u_view", Camera::currentCamera->view());
	Get().m_shader.setInt("color", color);
	auto anomaly = std::find(vertices.begin(), vertices.end(), glm::vec3(0)) != vertices.end();
	Get().m_mesh.setVertices(&vertices[0], vertices.size() * 3, Get().m_mesh._VAO, Get().m_mesh._VBO);
	Get().m_mesh.setAttributes(0, 3, GL_FLOAT, GL_TRUE, 3 * sizeof(float), (void*)(0));
	glPointSize(10.0f);
	glLineWidth(5.0f);
}

