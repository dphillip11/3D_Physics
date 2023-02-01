
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
"gl_Position = vec4(aPos,0,2.0f);"
"}\0";

const char* vertexShaderSource2 = "#version 330\n"
"layout(location = 0) in vec2 aPos;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(aPos,0,3.0f);"
"}\0";

//fragment shader source
const char* fragmentShaderSource = "#version 330\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"FragColor = vec4(gl_FragCoord.x / 800, 0.5f * gl_FragCoord.y / 600 ,0.0f,1.0f);\n"
"}\0";

//fragment shader source 2
const char* fragmentShaderSource2 = "#version 330\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"FragColor = vec4(0.2f,1.0f,0.5f,0.1f);\n"
"}\0";



int main()
{
    //setup window and make a reference
    GLFWwindow* window = InitialiseWindow(SCR_WIDTH, SCR_HEIGHT, windowName);

    unsigned int shaderProgram1;
    //compile and link source code for shaders
    CreateShaderProgram(vertexShaderSource, fragmentShaderSource, shaderProgram1);

    unsigned int shaderProgram2;
    CreateShaderProgram(vertexShaderSource2, fragmentShaderSource2, shaderProgram2);


    //create list of vertices
    float vertices[] = {
        -0.5f,-0.5f,
        0.0f,0.5f,
        0.5f,-0.5f,
        -0.25f,0.0f,
        0.25f,0.0f,
        0.0f,-0.5f
    };

    float vertices2[] = {
         -0.9f, -0.9f,
         0.9f, -0.9f,
          0.9f,  0.9f,

         0.9f,  0.9f,
         -0.9f,  0.9f,
         -0.9f, -0.9f
    };

    int indicesT1[] = { 
        0,3,5,
        1,3,4,
        5,4,2 };

    int indicesT2[] = {
        3,4,5
    };

    //create VAO to store VBO at attribute information
    unsigned int VAO[2];
    unsigned int VBO[2];
    glGenVertexArrays(2, VAO);
    glGenBuffers(2, VBO);

    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    //assign vertices to buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    //set vertex attributes on currently assigned buffer
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //assign vertice2 VAO,VBO
    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    //create EBO to index vertices
    unsigned int EBO[2];
    glGenBuffers(2, EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
    //push indiecs to buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesT1), indicesT1, GL_STATIC_DRAW);
    //bind a second EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesT2), indicesT2, GL_STATIC_DRAW);

    
    


    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram1);//draw plain color
        glBindVertexArray(VAO[1]);//screen corners
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glDrawArrays(GL_TRIANGLES, 0, 6);//fill screen

        glUseProgram(shaderProgram2);//draw with varied color
        glBindVertexArray(VAO[0]);//triangle vertices
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);//smaller triangles
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//wireframe mode
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);//9 vertices
 
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);//fill mode
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[1]);//inner triangle
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);//3 vertices

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

