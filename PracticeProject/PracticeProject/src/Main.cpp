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

void ProcessInput(Window& window, glm::vec3 &rotation);

int main()
{
   //setup window and make a reference
    Window window(SCR_WIDTH, SCR_HEIGHT, windowName);

    Ball ball = Ball(1);
    WoodenPanel panel;
    
    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    glm::mat4 view = glm::mat4(1.0f);
    //move camera
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    

    float deltaTime = 0;
    float time = 0;
   
    glEnable(GL_DEPTH_TEST);
    // render loop
    // -----------
    while (!window.closed())
    {
        
        

        //clear screen, clear fragment shader z values
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        ProcessInput(window, ball.rotation);
        ball.sphereShader->use();
        glm::mat4 ball_model = glm::mat4(1);
        ball_model = ball.generate_transform();
        ball.sphereShader->setMat4("model", ball_model);
        ball.sphereShader->setMat4("projection", projection);
        ball.sphereShader->setMat4("view", view);
        ball.shadedDraw(GL_LINE);

        /*glm::mat4 model = glm::mat4(1);
        model = panel.generate_transform();
        panel.shader->use();
        panel.shader->setMat4("model", model);
        panel.shader->setMat4("projection", projection);
        panel.shader->setMat4("view", view);
        panel.shadedDraw();*/
        
        time += deltaTime;

        ScopedTimer timer(&deltaTime);
                
        window.update();
        
    }
    window.terminate();
    return 0;
}

void ProcessInput(Window& window, glm::vec3& rotation)
{
    while (!window.input.empty())
    {
        if (window.input.front() == 1)
        {
            rotation.x += 0.01f ;
            window.input.pop();
        }
        else if (window.input.front() == 2)
        {
            rotation.x -= 0.01f;
            window.input.pop();
        }
        else if (window.input.front() == 3)
        {
            rotation.y += 0.01f;
            window.input.pop();
        }
        else if (window.input.front() == 4)
        {
            rotation.y -= 0.01f;
            window.input.pop();
        }
    }
}

