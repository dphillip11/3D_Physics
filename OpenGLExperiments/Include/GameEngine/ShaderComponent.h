#pragma once
#include "Component.h"
#include <string>

namespace glm {
	class mat4;
	class vec3;
}
using GLenum = int;
using GLuint = GLuint;

class ShaderComponent : public Component {
public:
	ShaderComponent(int gameObjectID) : Component(gameObjectID) {};

	void Setup(const std::string& vertex_shader_path, const std::string& fragment_shader_path);


	~ShaderComponent();

	void Use() const;

	void Unuse() const;

	GLuint GetProgram() const;

	void SetModelMatrix(const glm::mat4& model_matrix) const;

	void SetViewMatrix(const glm::mat4& view_matrix) const;

	void SetProjectionMatrix(const glm::mat4& projection_matrix) const;

	void SetBool(const std::string& name, bool value) const;
	// ------------------------------------------------------------------------
	void SetInt(const std::string& name, int value) const;
	// ------------------------------------------------------------------------
	void SetFloat(const std::string& name, float value) const;

	void SetVec3(const std::string& name, glm::vec3 value) const;

	void SetMat4(const std::string& name, const glm::mat4& mat) const;


	void Update(float deltaTime) override {}

	void Render() override {}

private:
	GLuint program_{ 0 };
	int model_uniform_{ 0 };
	int view_uniform_{ 0 };
	int projection_uniform_{ 0 };

	std::string LoadShaderFromFile(const std::string& path) const;

	void CheckCompileErrors(GLuint shader, std::string type) const;

	GLuint CompileShader(const std::string& source, GLenum type) const;

	GLuint LinkShaders(GLuint vertex_shader, GLuint fragment_shader) const;

};
