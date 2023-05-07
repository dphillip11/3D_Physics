#include "Window.h"
#include <iostream>
#include <vector>
#include "ScopedTimer.h"
#include "Input.h"
#include "Program.h"
#include "Programs/LoadOBJ.h"
#include "Programs/Newtons_Cradle.h"
#include "Programs/BallPhysics.h"

void displayFrameRate(float& timer, float& deltaTime, int& frames);

// settings
const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;
const char* windowName = "Window";

// setup window and make a reference
Window window(SCR_WIDTH, SCR_HEIGHT, windowName);
Window& Program::_window = window;

int main()
{
	// set background color
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.2f, 0.3f, 0.6f, 1.0f);

	float deltaTime = 0;
	float time = 0;
	int frames = 0;
	float frame_timer = 0;
	int programIndex = 0;
	int numberOfPrograms = 0;

	LoadOBJ L;
	Newtons_Cradle N;
	BallPhysics B;

	Program::SetupPrograms(window);


	// render loop
	while (!window.closed())
	{
		ScopedTimer timer(&deltaTime);
		time += deltaTime;

		if (time > 5) {
			Program::NextProgram();
			time = 0;
		}

		Program::RunProgram(deltaTime);

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
	if (timer > 1) {
		printf("%f ms/frame\n", 1000.0 / static_cast<double>(frames));
		timer = 0;
		frames = 0;
	}
}







