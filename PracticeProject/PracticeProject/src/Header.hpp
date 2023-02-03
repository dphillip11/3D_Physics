#pragma once
#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
GLFWwindow* InitialiseWindow(const unsigned int width, const unsigned int height, const char* name);

struct Vector3 {
    float x;
    float y;
    float z;

    Vector3 operator+=(Vector3 a) {
        return { x += a.x,y += a.y, z += a.z };
    }
};