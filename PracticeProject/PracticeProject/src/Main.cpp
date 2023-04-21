#include "Classes/Window.h"
#include <iostream>
#include <vector>
#include "Classes/ScopedTimer.h"
#include "Classes/Input.h"
#include "Classes/Program.h"
#include "Programs/LoadOBJ.h"
#include "Programs/Newtons_Cradle.h"
#include "Programs/BallPhysics.h"

void displayFrameRate(float& timer, float& deltaTime, int& frames);

    // settings
    const unsigned int SCR_WIDTH = 1280;
    const unsigned int SCR_HEIGHT = 720;
    const char* windowName = "Window";


    int main()
    {
        // setup window and make a reference
        Window window(SCR_WIDTH, SCR_HEIGHT, windowName);
        // set background color
        glEnable(GL_DEPTH_TEST);
        glClearColor(0.2f, 0.3f, 0.6f, 1.0f);
        
        float deltaTime = 0;
        float time = 0;
        int frames = 0;
        float frame_timer = 0;
        int programIndex = 0;
        int numberOfPrograms = 0;

        std::vector<Program*> programs;

        LoadOBJ L;
        Newtons_Cradle N;
        BallPhysics B;

        programs.push_back(reinterpret_cast<Program*>(&N));
        programs.push_back(reinterpret_cast<Program*>(&L));
        programs.push_back(reinterpret_cast<Program*>(&B));

        for (auto program : programs){
            program->Setup();
        }

        numberOfPrograms = programs.size();
        window.input->observers.push_back(B.getInputHandler());

        // render loop
        // -----------
        while (!window.closed())
        {
            ScopedTimer timer(&deltaTime);
            time += deltaTime;
            programs[2]->Run(deltaTime);
          /*if (time > 5){
                programIndex = (programIndex + 1) % numberOfPrograms;
                window.input->observers.clear();
                InputObserver* inputHandler = programs[programIndex]->getInputHandler();
                if (inputHandler != nullptr)
                    window.input->observers.push_back(inputHandler);
                time = 0;
            }

            programs[programIndex]->Run(deltaTime);*/
            
            displayFrameRate(frame_timer, deltaTime, frames);
            window.input->ProcessInput(deltaTime);
            window.update();

        }
        window.terminate();
        return 0;
    }




    void displayFrameRate(float& timer, float& deltaTime, int& frames)
    {
        frames++;
        timer += deltaTime;
        if (timer > 1){
            printf("%f ms/frame\n", 1000.0 / static_cast<double>(frames));
            timer = 0;
            frames = 0;
        }
    }


    




