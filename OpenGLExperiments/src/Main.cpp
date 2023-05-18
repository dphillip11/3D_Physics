#include "PCH/pch.h"
#include "Window.h"
#include "Input.h"
#include "Program.h"
#include "Programs/LoadOBJ.h"
#include "Programs/Newtons_Cradle.h"
#include "Programs/BallPhysics.h"
#include "Programs/GameEngine.h"
#include "GameEngine/GUI.h"

// settings
const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;
const char* windowName = "Window";

// setup window and make a reference
Window window(SCR_WIDTH, SCR_HEIGHT, windowName);
Window& Program::_window = window;


int main()
{

	GUI gui;
	gui.Init(window.window);

	// set background color
	glEnable(GL_DEPTH_TEST);
	window.clearColor = glm::vec3(0.2f, 0.3f, 0.6f);

	float deltaTime = 0;

	GameEngine GE;
	LoadOBJ L;
	Newtons_Cradle N;
	BallPhysics B;

	Program::SetupPrograms(window);

	// render loop
	while (!window.closed())
	{



		ScopedTimer timer(&deltaTime);

		Program::RunProgram(deltaTime);

		gui.Render();

		//displayFrameRate(frame_timer, deltaTime, frames);
		window.input->ProcessInput(deltaTime);
		window.update();

	}

	gui.Close();

	window.terminate();
	return 0;
}








