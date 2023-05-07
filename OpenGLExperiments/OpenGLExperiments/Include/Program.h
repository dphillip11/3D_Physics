#pragma once
#include "InputObserver.h"
#include "Camera.h"

class Program {
private:
	static std::vector<Program*> _programs;
	static Window& _window;
	static int _currentProgram;

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
		}
	}

	static void RunProgram(float deltaTime)
	{
		_programs[_currentProgram]->Run(deltaTime);
	}

	static void NextProgram()
	{
		_window.input->observers.clear();
		_currentProgram = (_currentProgram + 1) % _programs.size();
		_window.input->observers.push_back(_programs[_currentProgram]->getInputHandler());
	}

	virtual InputObserver* getInputHandler() = 0;
	virtual void Setup() = 0;
	virtual void Run(float deltaTime) = 0;

};

int Program::_currentProgram = 0;
std::vector<Program*> Program::_programs;
