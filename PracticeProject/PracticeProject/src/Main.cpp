
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
    Shader shaderColor = Shader("src/shaders/3DPos4DColor.vs", "src/shaders/3DPos4DColor.fs");

    //vertices for a square
    float vertices[] = {//clockwise
        -0.5f,0.5f,0.0f,//topleftfront,0
        0.5f,0.5f,0.0f,//toprightfront,1
        0.5f,-0.5f,0.0f,//bottomrightfront,2
        -0.5f,-0.5f,0.0f//bottomleftfront,3  
    };

    //colored vertices for a square
    float c_vertices[] = {//clockwise
        //position          colors
        -0.5f,0.5f,0.0f,    1.0f,0.0f,0.0f,1.0f,    //topleftfront,0
        0.5f,0.5f,0.0f,     0.0f,1.0f,0.0f,1.0f,    //toprightfront,1
        0.5f,-0.5f,0.0f,    0.0f,0.0f,1.0f,1.0f,//bottomrightfront,2
        -0.5f,-0.5f,0.0f,    1.0f,1.0f,0.0f,1.0f   //bottomleftfront,3  
    };

    //indices to draw the triangles
    int indices[] = {
        0,1,2,
        0,2,3};

   
    Model frontSquare = Model();
    frontSquare.setVertices(c_vertices, sizeof(c_vertices) / sizeof(float));
    frontSquare.setIndices(indices, 6);
    //position attribute
    frontSquare.setAttributes(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
    //color attribute
    frontSquare.setAttributes(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));

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
        shaderColor.use();
        for (int i = 0; i < models.size(); i++)
        {
            positions[i] += velocities[i] * deltaTime;
            if (abs(positions[i].x) > 1)
            {
                velocities[i].x *= -1;
                positions[i].x += velocities[i].x * deltaTime;
            }
            if (abs(positions[i].y) > 1)
            {
                velocities[i].y *= -1;
                positions[i].y += velocities[i].y * deltaTime;
            }
            shader3D.setVec3("offset", positions[i]);
            shaderColor.setVec3("offset", positions[i]);
            if (i == 0)
            {
                models[i].draw();
                shader3D.use();
            }
            else
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

