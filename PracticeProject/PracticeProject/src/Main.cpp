#include "Classes/Window.h"
#include <iostream>
#include <vector>
#include "Classes/ScopedTimer.h"
#include "Classes/Input.h"
#include "Classes/Programs/RenderPlane.h"

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
        Camera* camera  = &RenderPlane::camera;
        //set background color
        glEnable(GL_DEPTH_TEST);
        glClearColor(0.2f, 0.3f, 0.6f, 1.0f);
 
        float deltaTime = 0;
        float time = 0;
        int frames = 0;
        float frame_timer = 0;

        RenderPlane::Setup();

       

        // render loop
        // -----------
        while (!window.closed())
        {
            ScopedTimer timer(&deltaTime);
            time += deltaTime;
            RenderPlane::Run(time);
            displayFrameRate(frame_timer, deltaTime, frames);
            window.input->ProcessInput(deltaTime, *camera);
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


    




