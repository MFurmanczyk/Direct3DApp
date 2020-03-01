#pragma once
#include "Window.h"

class Application
{
public:
	Application() : Window(1280, 720, "DirectX Application") {};
	int Run();
private:
	void DoFrame();
	Window Window;
};
