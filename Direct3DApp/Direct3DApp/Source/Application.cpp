#include "..\Include\Application.h"

int Application::Run()
{
	while (true)
	{
		if (const auto Ecode = Window::ProcessMessage())
		{
			return *Ecode;
		}
		DoFrame();
	}
}

void Application::DoFrame()
{
	Window.Graphics().EndFrame();
}
