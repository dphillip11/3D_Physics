#pragma once

#include "Material.h"

class Shader
{
public:
	// the program ID
	unsigned int ID{ 0 };
	Shader() {};
	// constructor reads and builds the shader
	Shader(const std::string& shaderPath);
	// use/activate the shader
	void Use();
	void Unuse();
	// utility uniform functions
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setVec3(const std::string& name, glm::vec3 value) const;
	void setMat4(const std::string& name, const glm::mat4& mat) const;
	void setMaterial(Material material) const;
	void setLight(Light light) const;
	void checkCompileErrors(unsigned int shader, std::string type);

	Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath);
	Shader(const char* vertexPath, const char* fragmentPath);

};