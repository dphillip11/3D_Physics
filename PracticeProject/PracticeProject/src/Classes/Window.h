#pragma once
#include <GLFW/glfw3.h>
#include <queue>

class Window {
	GLFWwindow* window = NULL;

public:
	std::queue<int> input;

	Window(const unsigned int width, const unsigned int height, const char* name);
	void captureInput();
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	bool closed();
	void update();
	void terminate();
};