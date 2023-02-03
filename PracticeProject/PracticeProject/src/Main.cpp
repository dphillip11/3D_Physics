
#include "Header.hpp"
#include <iostream>
#include "Classes/Shader.h"
#include "Classes/Model.h"
#include "Classes/Ball.h"
#include "Classes/Cube.h"

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const char* windowName = "Balls";


int main()
{
    //setup window and make a reference
    GLFWwindow* window = InitialiseWindow(SCR_WIDTH, SCR_HEIGHT, windowName);

    Shader shader3D = Shader("src/shaders/3Dmoving.vs", "src/shaders/Red.fs");

    //vertices for a square
    float vertices[] = {//clockwise
        -0.5f,0.5f,0.0f,//topleftfront,0
        0.5f,0.5f,0.0f,//toprightfront,1
        0.5f,-0.5f,0.0f,//bottomrightfront,2
        -0.5f,-0.5f,0.0f//bottomleftfront,3
        
    };

    //indices to draw the triangles
    int indices[] = {
        0,1,2,
        0,2,3};

    Model frontSquare = Model();
    frontSquare.setVertices(vertices, sizeof(vertices) / sizeof(float));
    frontSquare.setIndices(indices, 6);
    frontSquare.setAttributes(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    Model rearSquare = Model();
    rearSquare.setVertices(vertices, sizeof(vertices) / sizeof(float));
    rearSquare.setIndices(indices, 6);
    rearSquare.setAttributes(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    Ball ball;
    ball.CreateVertices(0.25f);

    Cube cube;
    cube.CreateVertices(0.25f);

    Vector3 Position1 = { 0.25,0.25,0 };
    Vector3 Position2 = { -0.25,-0.25,0 };
    Vector3 Position3 = { 0,0,0 };
    Vector3 Velocity = { 0.0004,0.00025,0};
    
    float t = 0;
    
    
    


    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        // clear screen
        glClear(GL_COLOR_BUFFER_BIT);
        //set shader
        shader3D.use();
        shader3D.setVec3("offset", Position1);
        //frontSquare.draw(GL_LINE);
        //shader3D.setVec3("offset", Position2);
        rearSquare.draw(GL_LINE);
        Position2 += Velocity;
        if (abs(Position2.x) > 0.75)
            Velocity.x *= -1;
        if (abs(Position2.y) > 0.75)
            Velocity.y *= -1;
        shader3D.setVec3("offset", Position2);
        ball.draw(GL_LINE);
        shader3D.setVec3("offset", Position3);
        cube.draw();
        

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

