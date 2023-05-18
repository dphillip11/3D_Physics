#include "GLFW/GLFW3.h"
#include "GameEngine/TransformComponent.h"

#pragma once
class GUI {
public:
	void Init(GLFWwindow* window);

	void Render();

	void Close();

private:

	void DisplayHierarchy();

	void DisplaySpawnButton();

	void DisplayDemoWindow();

	void DisplaySystemWindow();

	void DisplayGameObject(int id);

	void DisplayTransform(int id);

	void DisplayTransformInfo(TransformComponent*& transform);

	void DisplayRigidBody(int id);

	void DisplayBoxCollider(int id);

	bool hierarchy_window = true;
	bool system_window = true;
	bool demo_window = false;
	const char* glsl_version = "#version 130";
	GLFWwindow* m_window;
	ImGuiIO* io;
};