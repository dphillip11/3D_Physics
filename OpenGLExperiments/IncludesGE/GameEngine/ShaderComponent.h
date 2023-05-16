#pragma once
#include "Component.h"
#include <string>
#include "Shader.h"


class ShaderComponent : public Component {
public:
	ShaderComponent(int gameObjectID, const char* filepath);
	ShaderComponent(int gameObjectID, const char* filepath1, const char* filepath2);

	void Update(float deltaTime) override {}

	void Render() override;

	void Use() {
		m_shader.Use();
	}
	void Unuse() {
		m_shader.Use();
	}
	// utility uniform functions
	void setBool(const std::string& name, bool value) const {
		m_shader.setBool(name, value);
	}
	void setInt(const std::string& name, int value) const {
		m_shader.setInt(name, value);
	}
	void setFloat(const std::string& name, float value) const {
		m_shader.setFloat(name, value);
	}
	void setVec3(const std::string& name, glm::vec3 value) const {
		m_shader.setVec3(name, value);
	}
	void setMat4(const std::string& name, const glm::mat4& mat) const {
		m_shader.setMat4(name, mat);
	}

	void SetModelMatrix(glm::mat4 mat)
	{
		m_shader.setMat4("u_model", mat);
	}
	void SetProjectionMatrix(glm::mat4 mat)
	{
		m_shader.setMat4("u_projection", mat);
	}
	void SetViewMatrix(glm::mat4 mat)
	{
		m_shader.setMat4("u_view", mat);
	}

	void SetViewPosAuto();

private:
	Shader m_shader;
};
