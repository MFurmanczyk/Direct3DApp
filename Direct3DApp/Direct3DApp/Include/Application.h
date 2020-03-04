#pragma once
#include "Window.h"
#include "Timer.h"

class Application
{
public:
	Application() : Window(1920, 1080, "DirectX Application") {};
	int Run();
private:
	void DoFrame();
	Window Window;
	Timer timer;
};
