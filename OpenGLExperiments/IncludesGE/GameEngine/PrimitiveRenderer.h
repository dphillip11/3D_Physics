#pragma once
#include <vector>
#include <glm/vec3.hpp>
#include <GameEngine/Mesh.h>
#include <Shader.h>


class PrimitiveRenderer {
public:
	static PrimitiveRenderer& Get() {
		static PrimitiveRenderer instance;
		return instance;
	}

	void DrawPoints(const std::vector<glm::vec3>& vertices, int color = 0);
	void DrawLines(const std::vector<glm::vec3>& vertices, int color = 0);
private:
	void _Draw(const std::vector<glm::vec3>& vertices, int color);
	PrimitiveRenderer();
	Mesh m_mesh;
	Shader m_shader;
};