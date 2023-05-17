#include "PCH/pch.h"
#include "Window.h"
#include "Input.h"
#include "Program.h"
#include "Programs/LoadOBJ.h"
#include "Programs/Newtons_Cradle.h"
#include "Programs/BallPhysics.h"
#include "Programs/GameEngine.h"

// settings
const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;
const char* windowName = "Window";

// setup window and make a reference
Window window(SCR_WIDTH, SCR_HEIGHT, windowName);
Window& Program::_window = window;
auto imgui_window = false;
auto system_window = false;
auto demo_window = true;

int main()
{
	const char* glsl_version = "#version 130";
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window.window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);
	imgui_window = true;
	system_window = true;
	ImGui::GetIO().WantCaptureMouse = true;


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
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGui::ShowDemoWindow(&demo_window);
		ImGui::Begin("Hierarchy", &imgui_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)


		if (ImGui::Button("Next Program"))
			Program::NextProgram();

		ScopedTimer timer(&deltaTime);

		Program::RunProgram(deltaTime);

		ImGui::End();
		ImGui::Begin("System Window", &system_window);
		ImGui::ColorEdit3("clear color", (float*)&window.clearColor);
		ImGui::DragFloat3("Camera Position", reinterpret_cast<float*>(&Camera::currentCamera->_position.x));
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
		ImGui::End();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		//displayFrameRate(frame_timer, deltaTime, frames);
		window.input->ProcessInput(deltaTime);
		window.update();

	}
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	window.terminate();
	return 0;
}








