#include "Classes/Window.h"
#include <iostream>
#include "Classes/Shader.h"
#include "Classes/Model.h"
#include "Classes/Ball.h"
#include "Classes/WoodenPanel.h"
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

void ProcessInput(Window& window, glm::vec3 &rotation, glm::mat4 &view);

int main()
{
   //setup window and make a reference
    Window window(SCR_WIDTH, SCR_HEIGHT, windowName);

    Ball ball = Ball(0.5);
    WoodenPanel panel;
    panel.rotation.x = -89;
    panel.position = glm::vec3(0, 0, -0.5);
    
    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    glm::mat4 view = glm::mat4(1.0f);
    //move camera
    view = glm::translate(view, glm::vec3(0.0f, -0.1f, -3.0f));
    //view = glm::rotate(view, glm::radians(15.0f), glm::vec3(1, 0, 0));

    

    float deltaTime = 0;
    float time = 0;
   
    glEnable(GL_DEPTH_TEST);
    // render loop
    // -----------
    while (!window.closed())
    {
        
        

        //clear screen, clear fragment shader z values
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        ProcessInput(window, ball.rotation, view);
        ball.sphereShader->use();
        glm::mat4 ball_model = glm::mat4(1);
        ball_model = ball.generate_transform();
        ball.sphereShader->setMat4("model", ball_model);
        ball.sphereShader->setMat4("projection", projection);
        ball.sphereShader->setMat4("view", view);
        ball.sphereShader->setFloat("radius", ball.radius);
        ball.shadedDraw(GL_LINE);

        glm::mat4 model = glm::mat4(1);
        model = panel.generate_transform();
        panel.shader->use();
        panel.shader->setMat4("model", model);
        panel.shader->setMat4("projection", projection);
        panel.shader->setMat4("view", view);
        panel.shadedDraw();
        
        time += deltaTime;

        ScopedTimer timer(&deltaTime);
                
        window.update();
        
    }
    window.terminate();
    return 0;
}

void ProcessInput(Window& window, glm::vec3& rotation, glm::mat4& view)
{
    while (!window.input.empty())
    {
        //up
        if (window.input.front() == 1)
        {
            rotation.x += 0.01f ;
            window.input.pop();
        }
        //down
        else if (window.input.front() == 2)
        {
            rotation.x -= 0.01f;
            window.input.pop();
        }
        //left
        else if (window.input.front() == 3)
        {
            rotation.y += 0.01f;
            window.input.pop();
        }
        //right
        else if (window.input.front() == 4)
        {
            rotation.y -= 0.01f;
            window.input.pop();
        }
        //Z
        else if (window.input.front() == 5)
        {
            view = glm::translate(view, glm::vec3(0.0f, 0.0f, -0.001f));
            window.input.pop();
        }
        //X
        else if (window.input.front() == 6)
        {
            view = glm::translate(view, glm::vec3(0.0f, 0.0f, 0.001f));
            window.input.pop();
        }
    }
}

