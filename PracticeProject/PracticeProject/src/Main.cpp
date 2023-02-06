#include "Classes/Window.h"
#include <iostream>
#include "Classes/Shader.h"
#include "Classes/Model.h"
#include "Classes/Ball.h"
#include "Classes/Cube.h"
#include "Classes/Texture.h"
#include <vector>
#include "Classes/ScopedTimer.h"

#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>


// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const char* windowName = "Balls";

void ProcessInput(Window& window, float& blend_value, Shader& shader);

int main()
{
   //setup window and make a reference
    Window window(SCR_WIDTH, SCR_HEIGHT, windowName);

    Shader shaderTexture = Shader("src/shaders/Pos3Color4Tex2.vs", "src/shaders/applyTexture.fs");
    Shader shaderTransform = Shader("src/shaders/3D.vs", "src/shaders/Red.fs");

    

   //vertices with texture coordinates
    float vertices[] = {//clockwise
        //position          colors                  texture coords
        -0.5f,0.5f,0.0f,    1.0f,0.0f,0.0f,1.0f,    0.0f, 1.0f,         //topleftfront,0
        0.5f,0.5f,0.0f,     0.0f,1.0f,0.0f,1.0f,    1.0f, 1.0f,         //toprightfront,1
        0.5f,-0.5f,0.0f,    0.0f,0.0f,1.0f,1.0f,    1.0f, 0.0f,         //bottomrightfront,2
        -0.5f,-0.5f,0.0f,    1.0f,1.0f,0.0f,1.0f,    0.0f, 0.0f         //bottomleftfront,3  
    };

    //indices to draw the triangles
    int indices[] = {
        0,1,2,
        0,2,3};

   
    Model frontSquare = Model();
    frontSquare.setVertices(vertices, sizeof(vertices) / sizeof(float));
    frontSquare.setIndices(indices, 6);
    //position attribute
    frontSquare.setAttributes(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
    //color attribute
    frontSquare.setAttributes(1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
    //texture attribute
    frontSquare.setAttributes(2, 2 , GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(7 * sizeof(float)));


    Ball ball(0.5);
    Cube cube(0.5);

    //create vector of models
    std::vector<Model> models;

    models.push_back(frontSquare);
    //models.push_back(ball);
    //models.push_back(cube);
    
    std::vector<Vector3> velocities;
    velocities.push_back({ 0.25,0.25,0 });
    //velocities.push_back({ -0.15,-0.35,0 });
    //velocities.push_back({ -0.05,-0.015,0 });

    std::vector<Vector3> positions;
    positions.push_back({ 0,0,0 });
    //positions.push_back({ 0,0,0 });
    //positions.push_back({ 0,0,0 });
    
    
    
    Texture texture1;
    texture1.setParameters();
    texture1.loadImage("src/Textures/container.jpg");
    Texture texture2;
    texture2.setParameters();
    texture2.loadImage("src/Textures/awesomeface.png", GL_RGBA, true);
    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    texture1.bind();
    glActiveTexture(GL_TEXTURE1);
    texture2.bind();

    shaderTexture.use(); // don't forget to activate/use the shader before setting uniforms!
    shaderTexture.setInt("texture1", 0);
    shaderTexture.setInt("texture2", 1);

    float blend_value = 1.0f;
    shaderTexture.setFloat("blend", blend_value);
    float deltaTime = 0;
    float time = 0;
   
    // render loop
    // -----------
    while (!window.closed())
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::rotate(trans, glm::radians(100 * time), glm::vec3(1.0, 1.0, 1.0));
        trans = glm::scale(trans, glm::vec3(sin(time), sin(time), sin(time)));
        unsigned int transformLoc = glGetUniformLocation(shaderTransform.ID, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
        shaderTransform.use();
        //cube.draw();
        ball.draw();
        //shaderTexture.use();
        time += deltaTime;
        /*trans = glm::mat4(1.0f);
        trans = glm::translate(trans, glm::vec3(-positions[0].x - 1,-positions[0].y + 1,-positions[0].z));
        trans = glm::scale(trans, glm::vec3(1 + sin(time), 1 + sin(time), 0.5));
        transformLoc = glGetUniformLocation(shaderTexture.ID, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));*/
        //models[0].draw();

       /* trans = glm::mat4(1.0f);
        glm::rotate(trans, glm::radians(400 * time), glm::vec3(0.0, 0.0, 1.0));
        trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
        */
        ScopedTimer timer(&deltaTime);
        
        ProcessInput(window, blend_value, shaderTexture);

       
        
        //shaderTexture.use();
        
        
       /* for (int i = 0; i < models.size(); i++)
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
            
            shaderTexture.setVec3("offset", positions[i]);*/
            //models[i].draw();
               
            
        //}
        
        window.update();
        
    }
    window.terminate();
    return 0;
}

void ProcessInput(Window& window, float& blend_value, Shader& shader)
{
    while (!window.input.empty())
    {
        if (window.input.front() == 1)
        {
            blend_value = fmin(blend_value + 0.0001f, (float)1);
            window.input.pop();
            shader.setFloat("blend", blend_value);
        }
        else
        {
            blend_value = fmax(blend_value - 0.0001f, (float)0);
            window.input.pop();
            shader.setFloat("blend", blend_value);
        }
    }
}

