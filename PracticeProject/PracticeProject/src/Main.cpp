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
#include "Classes/Input.h"
   


//#define GET_FRAMERATE() do{\
//    frames++;\
//\
//    if (time > 1)\
//    {\
//        printf("%f ms/frame\n", 1000.0 / double(frames));\
//        time = 0;\
//        frames = 0;\
//    }\
//} while (0);   \
//\


    // settings
    const unsigned int SCR_WIDTH = 800;
    const unsigned int SCR_HEIGHT = 600;
    const char* windowName = "Balls";



    int main()
    {
        //setup window and make a reference
        Window window(SCR_WIDTH, SCR_HEIGHT, windowName);
        //setup camera
        Camera camera  = Camera(glm::vec3(0, 2, -3), glm::vec3(0, 0, 0));
        //set background color
        glEnable(GL_DEPTH_TEST);
        glClearColor(0.2f, 0.3f, 0.6f, 1.0f);
       
        Ball ball = Ball(0.5);
        Box box = Box();
        box.createBoxTransforms(100);

        glm::mat4 projection;
        projection = glm::perspective(glm::radians(50.0f), 800.0f / 600.0f, 0.1f, 100.0f);

        float deltaTime = 0;
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
            window.input->ProcessInput(deltaTime,camera);
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

    




