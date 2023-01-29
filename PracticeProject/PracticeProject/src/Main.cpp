#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <iostream>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);


int main()
{
    glfwInit();
    //set version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // set GLFW profile, core is the basic/minimal version
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // create window reference
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    //if window is resized
    
    //registers with built in callback
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    //initialise GLAD to deal with function pointers for openGL
    //loads the address of OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    //render loop
    while (!glfwWindowShouldClose(window))
    {
        //call process input every render cycle
        processInput(window);
        // rendering commands here
        //configures clear color
        glClearColor(1, 0, 0, 1.0f);
        //clears the screen using the clear color
        glClear(GL_COLOR_BUFFER_BIT);
        //exchange front and back buffer when render loop is complete
        glfwSwapBuffers(window);
        // check if events are triggered
        glfwPollEvents();
    }
    //properly exit
    glfwTerminate();

    return 0;
}

//when window is resize this function will be called
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

//
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}