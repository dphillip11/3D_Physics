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

        obj taxi;
        taxi.read("src/Assets/robot.obj");
        taxi.vertices = taxi.unravelIndices(taxi.vertices, taxi.vertexIndices);
        //taxi.normalMap = taxi.unravelIndices(taxi.normalMap, taxi.normalIndices);
 
        Model taxi_model;
        taxi_model.shader = std::make_unique<Shader>("src/shaders/vertex/obj.hlsl", "src/shaders/fragment/obj.hlsl", "src/shaders/geometry/calculateNormals.hlsl");
        taxi_model.setVertices(&taxi.vertices[0], taxi.vertices.size()*3, taxi_model._VAO, taxi_model._VBO);
        taxi_model.setAttributes(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));

        
        Light light1{ glm::vec3(5), glm::vec3(0.4), glm::vec3(3), glm::vec3(1) };
        Material mat1{ glm::vec3(1), glm::vec3(1), glm::vec3(1), 32 };
      

       

        // render loop
        // -----------
        while (!window.closed())
        {
            
            glm::mat4 view = camera.lookAt();
            ScopedTimer timer(&deltaTime);
            time += deltaTime;

            
            taxi_model.shader->use();
            taxi_model.draw(GL_LINE);
            taxi_model.shader->setMat4("model", glm::translate(glm::mat4(1), glm::vec3(8, 2, 0)));
            taxi_model.draw();
            taxi_model.shader->setMat4("model", glm::translate(glm::mat4(1), glm::vec3(2)));
            taxi_model.shader->setMat4("view", camera.lookAt());
            taxi_model.shader->setMat4("projection", camera.projection);
            taxi_model.shader->setVec3("viewPosition", camera._position);
            taxi_model.shader->setLight(light1);
            taxi_model.shader->setMaterial(mat1);
            

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


    




