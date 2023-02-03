
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

    Shader shader1 = Shader("src/shaders/2D.vs", "src/shaders/ColorByPosition.fs");
    Shader shader2 = Shader("src/shaders/2D.vs", "src/shaders/ColorByTime.fs");
    Shader shader3D = Shader("src/shaders/3D.vs", "src/shaders/ColorByTime.fs");

      /*  double radius = 1.0;
        int n_segments = 8;
        auto vertices = sphere_vertices(radius, n_segments);
        auto indices = sphere_indices(n_segments);
        std::cout << "Vertices:" << std::endl;
        for (int i = 0; i < vertices.size(); i++) {
            auto [x, y, z] = vertices[i];
            std::cout << x << " " << y << " " << z << std::endl;
        }
        std::cout << "Indices:" << std::endl;
        for (int i = 0; i < indices.size(); i++) {
            std::cout << indices[i] << " ";
        }
        std::cout << std::endl;
        return 0;*/


    //create list of vertices
    float vertices[] = {
        -0.5f,-0.5f,
        0.0f,0.5f,
        0.5f,-0.5f,
        -0.25f,0.0f,
        0.25f,0.0f,
        0.0f,-0.76f
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

    Ball ball = Ball();
    ball.CreateVertices(0.5f);
    Cube cube = Cube();
    cube.CreateVertices(0.5f);
   /* model.setVertices(vertices, sizeof(vertices)/sizeof(float));
    model.setAttributes(0, 2, GL_FLOAT, false, 2 * sizeof(float), (void*)0);
    model.setIndices(indicesT1, sizeof(indicesT1)/sizeof(int));*/

    float t = 0;
    float dx = 0;
    float xPos = 0;
    float dy = 0;
    float yPos = 0;
    float dz = -0.0001;
    float zPos = 0;
    
    
    


    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        //set uniform float
        t = (t + 0.001f);
        xPos += dx;
        yPos += dy;
        zPos += dz;
        if (abs(xPos) > 1)
        {
            xPos -= dx;
            dx = -dx;
        }
        if (abs(yPos) > 1)
        {
            yPos -= dy;
            dy = -dy;
        }
        shader3D.setFloat("t", t);
        // clear screen
        glClear(GL_COLOR_BUFFER_BIT);
        //set shader
        shader3D.use();//draw with varied color
        //draw model
        shader3D.setFloat("x", xPos);
        shader3D.setFloat("y", yPos);
        shader3D.setFloat("z", zPos);
        //cube.draw(GL_FILL);
        ball.draw(GL_FILL);
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

