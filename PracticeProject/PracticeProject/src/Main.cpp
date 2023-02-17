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

void displayFrameRate(float& timer, float& deltaTime, int& frames);



    // settings
    const unsigned int SCR_WIDTH = 1200;
    const unsigned int SCR_HEIGHT = 800;
    const char* windowName = "Balls";



    int main()
    {
        //setup window and make a reference
        Window window(SCR_WIDTH, SCR_HEIGHT, windowName);
        //setup camera
        Camera camera  = Camera(glm::vec3(0, 0, -5), glm::vec3(0, 0, 0));
        //set background color
        glEnable(GL_DEPTH_TEST);
        //glClearColor(0.2f, 0.3f, 0.6f, 1.0f);
        //Box box;
        //box.createBoxTransforms(10);
        Ball ball;
        auto box = WoodenBox();
        float deltaTime = 0;
        float time = 0;
        int frames = 0;
        float frame_timer = 0;
        //Shader lit = Shader("src/shaders/vertex/ballLit.hlsl", "src/shaders/fragment/ballLit.hlsl");


        Light light =
        {
            glm::vec3(5, 5, 5),//position
            glm::vec3(1),//ambient
            glm::vec3(1),//diffuse
            glm::vec3(1)//specular
        };
        Material lightbox =
        {
            glm::vec3(10),//ambient
            glm::vec3(10),//diffuse
            glm::vec3(10),//specular
            32 //shininess
        };



        // render loop
        // -----------
        while (!window.closed())
        {
         
            glm::mat4 view = camera.lookAt();
            ScopedTimer timer(&deltaTime);
            time += deltaTime;
            box.shader->use();
            box.transform = glm::mat4(1);
            box.setUniforms(camera);
            box.shader->setLight(light);
            box.shader->setFloat("time",time);
            box.shadedDraw();

            box.transform = glm::translate(glm::mat4(1), glm::vec3(5, 5, 5));
            box.setUniforms(camera);
            box.shader->setMaterial(lightbox);
            box.shadedDraw();
            //light source
            /*ball.shader->use();
            ball.shader->setMat4("MVP", camera.projection * camera.lookAt() * glm::translate(glm::mat4(1), glm::vec3(5, 5, 5)));
            ball.shadedDraw();*/
            
            //displayFrameRate(frame_timer, deltaTime, frames);
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


    




