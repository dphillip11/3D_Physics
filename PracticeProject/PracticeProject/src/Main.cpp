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
#include "Classes/Box.h"

#define GET_FRAMERATE() do{\
    frames++;\
\
    if (time > 1)\
    {\
        printf("%f ms/frame\n", 1000.0 / double(frames));\
        time = 0;\
        frames = 0;\
    }\
} while (0);\
  

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const char* windowName = "Balls";

void ProcessInput(Window& window, glm::mat4 &transform, glm::mat4 &view);

int main()
{
   //setup window and make a reference
    Window window(SCR_WIDTH, SCR_HEIGHT, windowName);

    Ball ball = Ball(0.5);
    Box box = Box();
    Box box2 = Box();
    Box box3 = Box();
    glm::mat4 transformation = glm::mat4(1.0f);
    transformation = glm::translate(transformation, glm::vec3(0.5, -0.3f, -3.0f));
    box2.transform(transformation);
    transformation = glm::translate(transformation, glm::vec3(-1, -0.6f, 3));
    box3.transform(transformation);
    
    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    glm::mat4 view = glm::mat4(1.0f);
    //move camera
    view = glm::translate(view, glm::vec3(0.0f, -0.3f, -3.0f));
    //view = glm::rotate(view, glm::radians(180.0f), glm::vec3(0, 1, 0));
    ball.transform = glm::translate(ball.transform, glm::vec3(1, 0, 0));
    

    float deltaTime = 0;
    float time = 0;
    int frames = 0;

   
    glEnable(GL_DEPTH_TEST);
    // render loop
    // -----------
    while (!window.closed())
    {        ScopedTimer timer(&deltaTime);
        time += deltaTime;
               
        //GET_FRAMERATE()
        

        //clear screen, clear fragment shader z values
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        ProcessInput(window, ball.transform, view);
        ball.sphereShader->use();
        ball.sphereShader->setMat4("model", ball.transform);
        ball.sphereShader->setMat4("projection", projection);
        ball.sphereShader->setMat4("view", view);
        ball.sphereShader->setFloat("radius", ball.radius);
        ball.shadedDraw(GL_LINE);

       /* glm::mat4 model = glm::mat4(1);
        model = panel.generate_transform();
        panel.shader->use();
        panel.shader->setMat4("model", model);
        panel.shader->setMat4("projection", projection);
        panel.shader->setMat4("view", view);
        panel.shadedDraw();*/
        
        box.draw(view,projection);

        box2.draw(view, projection);

        box3.draw(view, projection);
       glm::mat4 rotation = glm::mat4(1);
       rotation = glm::rotate(rotation, glm::radians(0.01f), glm::vec3(1, 1, 0));
        box.transform(rotation);
       window.update();
        
    }
    window.terminate();
    return 0;
}

void ProcessInput(Window& window, glm::mat4 &transform, glm::mat4& view)
{
    while (!window.input.empty())
    {
        //up
        if (window.input.front() == 1)
        {
            transform = glm::rotate(transform, glm::radians(0.05f), glm::vec3(1, 0, 0));
            window.input.pop();
        }
        //down
        else if (window.input.front() == 2)
        {
            transform = glm::rotate(transform, glm::radians(-0.05f), glm::vec3(1, 0, 0));
            window.input.pop();
        }
        //left
        else if (window.input.front() == 3)
        {
            transform = glm::rotate(transform, glm::radians(0.05f), glm::vec3(0, 1, 0));
            window.input.pop();
        }
        //right
        else if (window.input.front() == 4)
        {
            transform = glm::rotate(transform, glm::radians(-0.05f), glm::vec3(1, 0, 0));
            window.input.pop();
        }
        //Z
        else if (window.input.front() == 5)
        {
            //transform = glm::translate(transform, glm::vec3(0.001, 0, 0));
            view = glm::translate(view, glm::vec3(0.0f, 0.0f, -0.001f));
            window.input.pop();
        }
        //X
        else if (window.input.front() == 6)
        {
            //transform = glm::translate(transform, glm::vec3(- 0.001, 0, 0));
            view = glm::translate(view, glm::vec3(0.0f, 0.0f, 0.001f));
            window.input.pop();
        }
    }
}


