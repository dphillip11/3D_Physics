#pragma once

#include <unordered_map>
#include <string>
#include "Shader.h"

class ShaderManager {
public:
	static ShaderManager& GetInstance() {
		static ShaderManager instance;
		return instance;
	}

	Shader& LoadShader(const char* filepath) {
		if (m_shaders.find(filepath) != m_shaders.end()) {
			return m_shaders[filepath];
		}
		Shader shader{ filepath };
		m_shaders[filepath] = shader;
		return m_shaders[filepath];
	}

	Shader& LoadShader(const char* filepath1, const char* filepath2) {
		if (m_shaders.find(filepath1) != m_shaders.end()) {
			return m_shaders[filepath1];
		}
		Shader shader{ filepath1, filepath2 };
		m_shaders[filepath1] = shader;
		return m_shaders[filepath1];
	}

private:
	ShaderManager() = default;
	std::unordered_map<std::string, Shader> m_shaders;
};


