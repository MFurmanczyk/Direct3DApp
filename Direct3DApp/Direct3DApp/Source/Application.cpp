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
	const float c = sin(timer.Peek()) / 2.f + .5f;
	Window.Graphics().ClearBuffer(1.f, c, c);
	Window.Graphics().EndFrame();
}
