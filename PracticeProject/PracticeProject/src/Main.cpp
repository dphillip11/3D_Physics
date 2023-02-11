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
#include "Libraries/glm/glm/glm.hpp"
#include "Libraries/glm/glm/gtc/matrix_transform.hpp"
#include "Libraries/glm/glm/gtc/type_ptr.hpp"
#include "Classes/Box.h"
#include "Libraries/glm/glm/gtc/quaternion.hpp"
#include "Classes/Camera.h"
#include "Classes/Input.h"
#include "Classes/BallManager.h"
   

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
       
       
        BallManager ballManager;
        ballManager.spawnBalls(1000);

        float deltaTime = 0;
        float time = 0;
        int frames = 0;
        float frame_timer = 0;

        glm::mat4 rotation = glm::rotate(glm::mat4(1), glm::radians(0.01f), glm::vec3(1, 1, 0));

        // render loop
        // -----------
        while (!window.closed())
        {
            glm::mat4 view = camera.lookAt();
            ScopedTimer timer(&deltaTime);
            time += deltaTime;
            ballManager.updatePositions(deltaTime);
            ballManager.drawBalls(view, camera.projection);
            displayFrameRate(frame_timer, deltaTime, frames);
            window.input->ProcessInput(deltaTime, camera, ballManager);
            window.update();

        }
        window.terminate();
        return 0;
    }

    




