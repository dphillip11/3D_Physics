#include "Classes/Window.h"
#include <iostream>
#include "Classes/Shader.h"
#include "Classes/Model.h"
#include "Classes/Texture.h"
#include <vector>
#include "Classes/ScopedTimer.h"
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include <glm/glm/gtc/quaternion.hpp>
#include "Classes/Camera.h"
#include "Classes/Input.h"
#include "Classes/obj.h"

void displayFrameRate(float& timer, float& deltaTime, int& frames);

    // settings
    const unsigned int SCR_WIDTH = 1280;
    const unsigned int SCR_HEIGHT = 720;

    int Window::_height = 1;
    int Window::_width = 1;
    const char* windowName = "Balls";


    int main()
    {
        //setup window and make a reference
        Window window(SCR_WIDTH, SCR_HEIGHT, windowName);
        //setup camera
        Camera camera  = Camera(glm::vec3(0, 5, -5), glm::vec3(2));
        //set background color
        glEnable(GL_DEPTH_TEST);
        glClearColor(0.2f, 0.3f, 0.6f, 1.0f);
 
        float deltaTime = 0;
        float time = 0;
        int frames = 0;
        float frame_timer = 0;

        obj butterfly;
        butterfly.read("src/Assets/taxi.obj");
        Model bFly;
        bFly.shader = std::make_unique<Shader>("src/shaders/vertex/obj.hlsl", "src/shaders/fragment/obj.hlsl");
        bFly.setVertices(&butterfly.vertices[0], butterfly.vertices.size(), bFly._VAO, bFly._VBO);
        bFly.setIndices(&butterfly.vertexIndices[0], butterfly.vertexIndices.size(), bFly._EBO);
        GLint posAttrib = glGetAttribLocation(bFly.shader->ID, "vertices");
        bFly.setAttributes(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));
        //bFly.setNormalMap(butterfly.normalMap, butterfly.normalIndices);
        


        // render loop
        // -----------
        while (!window.closed())
        {
            
            glm::mat4 view = camera.lookAt();
            ScopedTimer timer(&deltaTime);
            time += deltaTime;

            bFly.shader->use();
            bFly.draw(GL_LINE);
            bFly.shader->setMat4("model", glm::translate(glm::mat4(1), glm::vec3(8,2,0)));
            bFly.draw();
            Light light1{ glm::vec3(5), glm::vec3(0.1), glm::vec3(1), glm::vec3(1) };
            Material mat1{ glm::vec3(0,1,1), glm::vec3(0,1,1), glm::vec3(0,1,1), 101 };
            bFly.shader->setMat4("model", glm::translate(glm::mat4(1), glm::vec3(2)));
            bFly.shader->setMat4("view", camera.lookAt());
            bFly.shader->setMat4("projection", camera.projection);
            bFly.shader->setVec3("viewPosition", camera._position);
            bFly.shader->setLight(light1);
            bFly.shader->setMaterial(mat1);

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


    




