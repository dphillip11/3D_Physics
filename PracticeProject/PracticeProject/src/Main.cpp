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

void ProcessInput(Window& window, float& blend_value, Shader& shader);

int main()
{
   //setup window and make a reference
    Window window(SCR_WIDTH, SCR_HEIGHT, windowName);

    Ball ball = Ball(0.5);
    WoodenPanel panel;
 
    float deltaTime = 0;
    float time = 0;
   
    // render loop
    // -----------
    while (!window.closed())
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glEnable(GL_DEPTH_TEST);
        ball.position = glm::vec3(0.5 * sin(time), 0.5 * sin(time), 0);
        ball.rotation.x = 360 * sin(time/6);
        ball.shadedDraw();
        panel.shadedDraw();
        
        //shaderTex.use();
        //ball.draw(GL_LINE);

        time += deltaTime;

        ScopedTimer timer(&deltaTime);
                
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

