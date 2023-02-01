#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#define LOG(x) std::cout << x << std::endl;

void CreateShaderProgram(const char* &vertexShaderSource, const char* &fragmentShaderSource);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
GLFWwindow* InitialiseWindow(const unsigned int width, const unsigned int height, const char* name);