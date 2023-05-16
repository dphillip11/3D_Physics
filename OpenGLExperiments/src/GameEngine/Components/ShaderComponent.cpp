#include "PCH/pch.h"
#include "GameEngine/ShaderComponent.h"
#include "GameEngine/ShaderManager.h"
#include "GameEngine/Component.h"
#include "Camera.h"

ShaderComponent::ShaderComponent(int gameObjectID, const char* filepath) : Component(gameObjectID), m_shader(ShaderManager::GetInstance().LoadShader(filepath)) {}
ShaderComponent::ShaderComponent(int gameObjectID, const char* filepath1, const char* filepath2) : Component(gameObjectID), m_shader(ShaderManager::GetInstance().LoadShader(filepath1, filepath2)) {}


void ShaderComponent::SetViewPosAuto()
{
	m_shader.setMat4("u_projection", Camera::currentCamera->projection);
	m_shader.setMat4("u_view", Camera::currentCamera->view());
}

void ShaderComponent::Render()
{

}