#include "Window.h"
#include <iostream>
#include <vector>
#include "ScopedTimer.h"
#include "Input.h"
#include "Program.h"
#include "Programs/LoadOBJ.h"
#include "Programs/Newtons_Cradle.h"
#include "Programs/BallPhysics.h"
#include  "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"

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
	const char* glsl_version = "#version 130";
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window.window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);
	auto imgui_window = true;

	// set background color
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.2f, 0.3f, 0.6f, 1.0f);

	float deltaTime = 0;
	float time = 0;
	int frames = 0;
	float frame_timer = 0;
	int numberOfPrograms = 0;

	LoadOBJ L;
	Newtons_Cradle N;
	BallPhysics B;

	Program::SetupPrograms(window);


	// render loop
	while (!window.closed())
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("Another Window", &imgui_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
		ImGui::Text("This will change program!");
		if (ImGui::Button("Next Program"))
			Program::NextProgram();
		ImGui::End();
		ScopedTimer timer(&deltaTime);
		time += deltaTime;


		Program::RunProgram(deltaTime);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		displayFrameRate(frame_timer, deltaTime, frames);
		window.input->ProcessInput(deltaTime);
		window.update();

	}
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
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







