#pragma once
#include <GLFW/glfw3.h>
#include <queue>
#include <memory>
#include "Input.h"


class Window {
public:
	 static Window* instance;
	 GLFWwindow* window;
	 static int _height;
	 static int _width;
	 static std::unique_ptr<Input> input;
	 Window(const unsigned int width, const unsigned int height, const char* name);
	 void captureInput();
	 static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	 static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	 static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	 bool closed();
	 void update();
	 void terminate();
};




