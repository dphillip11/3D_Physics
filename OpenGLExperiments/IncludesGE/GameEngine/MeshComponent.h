#pragma once
#include "GameEngine/Component.h"
#include "GameEngine/Mesh.h"


class MeshComponent : public Component {
public:
	MeshComponent(int gameobjectID, const char* filepath);

	void Draw() {
		m_mesh.draw(GL_FILL);
	}

	void Update(float deltaTime) override {}

	void Render() override {}

	/*private*/
	Mesh& m_mesh;
};
