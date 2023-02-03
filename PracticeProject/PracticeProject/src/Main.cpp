
#include "Header.hpp"
#include <iostream>
#include "Classes/Shader.h"
#include "Classes/Model.h"
#include "Classes/Ball.h"
#include "Classes/Cube.h"
#include <vector>
#include "Classes/ScopedTimer.h"

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

    Ball ball(0.25);
    Cube cube(0.25);

    //create vector of models
    std::vector<Model> models;

    models.push_back(frontSquare);
    models.push_back(rearSquare);
    models.push_back(ball);
    models.push_back(cube);
    
    std::vector<Vector3> velocities;
    velocities.push_back({ 0.25,0.25,0 });
    velocities.push_back({-0.25,-0.25,0 });
    velocities.push_back({ -0.15,-0.35,0 });
    velocities.push_back({ -0.05,-0.015,0 });
    std::vector<Vector3> positions;
    positions.push_back({ 0,0,0 });
    positions.push_back({ 0,0,0 });
    positions.push_back({ 0,0,0 });
    positions.push_back({ 0,0,0 });
    
    float deltaTime = 0;
    
    


    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        ScopedTimer timer(&deltaTime);
        processInput(window);
        glClear(GL_COLOR_BUFFER_BIT);
        shader3D.use();
        for (int i = 0; i < models.size(); i++)
        {
            positions[i] += velocities[i] * deltaTime;
            if (abs(positions[i].x) > 1)
                velocities[i].x *= -1;
            if (abs(positions[i].y) > 1)
                velocities[i].y *= -1;
            shader3D.setVec3("offset", positions[i]);
            models[i].draw(GL_LINE);
        }
        

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

