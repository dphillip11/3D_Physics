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
#include "Classes/BallManager.h"
#include "Classes/CubeManager.h"
#include "Classes/ShaderExperiment.h"
#include "Classes/WoodenBox.h"
#include "Classes/rayTracing.h"
#include "Classes/obj.h"

void displayFrameRate(float& timer, float& deltaTime, int& frames);

    // settings
    const unsigned int SCR_WIDTH = 1800;
    const unsigned int SCR_HEIGHT = 1350;

    int Window::_height = 1;
    int Window::_width = 1;
    const char* windowName = "Balls";


    int main()
    {
        //setup window and make a reference
        Window window(SCR_WIDTH, SCR_HEIGHT, windowName);
        //setup camera
        Camera camera  = Camera(glm::vec3(0, 0, -5), glm::vec3(0, 0, 0));
        //set background color
        glEnable(GL_DEPTH_TEST);
        glClearColor(0.2f, 0.3f, 0.6f, 1.0f);
 
        float deltaTime = 0;
        float time = 0;
        int frames = 0;
        float frame_timer = 0;

        Shader shader = Shader("src/shaders/vertex/ballS.hlsl", "src/shaders/fragment/ball.hlsl");
        obj butterfly;
        butterfly.read("src/Assets/taxi.obj");
        Model bFly;
    
        bFly.setVertices(&butterfly.vertices[0], butterfly.vertices.size());
        bFly.setIndices(&butterfly.vertexIndices[0], butterfly.vertexIndices.size());
        bFly.setAttributes(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));
        



        // render loop
        // -----------
        while (!window.closed())
        {
         
            glm::mat4 view = camera.lookAt();
            ScopedTimer timer(&deltaTime);
            time += deltaTime;

            shader.use();
            bFly.draw();
            shader.setMat4("MVP", camera.projection * camera.lookAt() * glm::translate(glm::mat4(1), glm::vec3(5, 5, 5)));
            displayFrameRate(frame_timer, deltaTime, frames);
            window.input->ProcessInput(deltaTime, camera);
            window.update();

        }
        window.terminate();
        return 0;
    }




    void displayFrameRate(float& timer, float& deltaTime, int& frames)
    {
        frames++;
        timer += deltaTime;
        if (timer > 1)
        {
            printf("%f ms/frame\n", 1000.0 / double(frames));
            timer = 0;
            frames = 0;
        }
    }


    




