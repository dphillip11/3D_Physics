
#include "Header.hpp"


// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const char* windowName = "LearnOpenGl";

//vertex shader source
const char* vertexShaderSource = "#version 330\n"
"layout(location = 0) in vec2 aPos;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(aPos,0,1.0);"
"}\0";
//fragment shader source
const char* fragmentShaderSource = "#version 330\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"FragColor = vec4(1.0f,0.5f,0.2f,1.0f);\n"
"}\0";

int main()
{
       
    GLFWwindow* window = InitialiseWindow(SCR_WIDTH, SCR_HEIGHT, windowName);
    CreateShaderProgram(vertexShaderSource, fragmentShaderSource);

    //create list of vertices
    float vertices[] = {
        -0.5f,-0.5f,
        -0.5f,0.5f,
        0.5f,0.5f
    };
    // generate vertex buffer object
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //assign vertices to buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);





    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

