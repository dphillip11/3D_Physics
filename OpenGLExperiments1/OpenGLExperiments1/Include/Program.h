#pragma once
#include "InputObserver.h"
#include "Camera.h"

class Program {
private:
	static std::vector<Program*> _programs;
	static Window& _window;
	static int _currentProgram;

protected:
	Camera _camera{ glm::vec3(0), glm::vec3(0) };

public:

	Program() {
		_programs.push_back(this);
	}

	static void SetupPrograms(Window& window)
	{
		if (_programs.size() > 0)
		{
			_window = window;
			for (auto program : _programs)
			{
				program->Setup();
			}

			_window.input->observers.push_back(_programs[_currentProgram]->getInputHandler());
			Camera::currentCamera = &_programs[_currentProgram]->_camera;
		}
	}

	static void RunProgram(float deltaTime)
	{
		_programs[_currentProgram]->Run(deltaTime);
	}

	static void NextProgram()
	{
		_window.input->observers.clear();
		_currentProgram = (_currentProgram + 1) % (int)_programs.size();
		_window.input->observers.push_back(_programs[_currentProgram]->getInputHandler());
		Camera::currentCamera = &_programs[_currentProgram]->_camera;
	}

	virtual InputObserver* getInputHandler() = 0;
	virtual void Setup() = 0;
	virtual void Run(float deltaTime) = 0;

};

int Program::_currentProgram = 0;
std::vector<Program*> Program::_programs;
