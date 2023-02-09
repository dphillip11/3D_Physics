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
#include <glm/glm/gtc/quaternion.hpp>
#include "Classes/Camera.h"



    Camera* camera_ptr;
    Window* window_ptr;
    float deltaTime;
    


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
    float lastMouseX;
    float lastMouseY;
    bool firstMouse = true;
    const char* windowName = "Balls";

    void ProcessInput();

    int main()
    {
        //setup window and make a reference
        Window window(SCR_WIDTH, SCR_HEIGHT, windowName);
        window_ptr = &window;
        //setup camera
        Camera camera(glm::vec3(0, 2, -3), glm::vec3(0, 0, 0));
        camera_ptr = &camera;
        //set background color
        glEnable(GL_DEPTH_TEST);
        glClearColor(0.2f, 0.3f, 0.6f, 1.0f);
       
        Ball ball = Ball(0.5);
        Box box = Box();
        box.createBoxTransforms(100);

        glm::mat4 projection;
        projection = glm::perspective(glm::radians(50.0f), 800.0f / 600.0f, 0.1f, 100.0f);




        deltaTime = 0;
        float time = 0;
        int frames = 0;

        glm::mat4 rotation = glm::rotate(glm::mat4(1), glm::radians(0.01f), glm::vec3(1, 1, 0));

        // render loop
        // -----------
        while (!window.closed())
        {
            ScopedTimer timer(&deltaTime);
            time += deltaTime;

            //GET_FRAMERATE()
            ProcessInput();
            glm::mat4 view = camera.lookAt();
            ball.sphereShader->use();
            ball.sphereShader->setMat4("MVP", projection * view * ball.transform);
            ball.sphereShader->setFloat("radius", ball.radius);
            ball.shadedDraw();
            box.drawBoxes(view, projection);
            box.transform(rotation);
            window.update();

        }
        window.terminate();
        return 0;
    }

    void ProcessInput()
    {
        const float cameraSpeed = 0.05f;
        const float mouseSensitivity = 0.1f;
        if (firstMouse)
        {
            lastMouseX = window_ptr->mouseX;
            lastMouseY = window_ptr->mouseY;
            firstMouse = false;
        }
        else
        {
            float mouseDX = mouseSensitivity * (window_ptr->mouseX - lastMouseX);
            lastMouseX = window_ptr->mouseX;
            float mouseDY = mouseSensitivity * (window_ptr->mouseY - lastMouseY);
            lastMouseY = window_ptr->mouseY;
            camera_ptr->rotate(mouseDX, mouseDY);
        }
        while (!window_ptr->input.empty())
        {
            //up
            if (window_ptr->input.front() == 1)
            {
                camera_ptr->moveForward(deltaTime * 5);
                window_ptr->input.pop();
            }
            //down
            else if (window_ptr->input.front() == 2)
            {
                camera_ptr->moveForward(-deltaTime * 5);
                window_ptr->input.pop();
            }
            //left
            else if (window_ptr->input.front() == 3)
            {
                camera_ptr->moveRight(-deltaTime * 5);
                window_ptr->input.pop();
            }
            //right
            else if (window_ptr->input.front() == 4)
            {
                camera_ptr->moveRight(deltaTime * 5);
                window_ptr->input.pop();
            }
            //Z
            else if (window_ptr->input.front() == 5)
            {
                //transform = glm::translate(transform, glm::vec3(0.001, 0, 0));
                //view = glm::translate(view, glm::vec3(0.0f, 0.0f, -0.001f));
                window_ptr->input.pop();
            }
            //X
            else if (window_ptr->input.front() == 6)
            {
                //transform = glm::translate(transform, glm::vec3(- 0.001, 0, 0));
                //view = glm::translate(view, glm::vec3(0.0f, 0.0f, 0.001f));
                window_ptr->input.pop();
            }
        }
    }




