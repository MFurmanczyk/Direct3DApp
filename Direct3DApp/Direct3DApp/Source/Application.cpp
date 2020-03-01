#include "..\Include\Application.h"

int Application::Run()
{
	MSG Message;
	BOOL gResult;
	while ((gResult = GetMessage(&Message, nullptr, NULL, NULL)) > 0)
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
		DoFrame();
	}
	if (gResult == -1)
	{
		throw Window::WindowException(__LINE__, __FILE__, GetLastError());
	}

	return Message.wParam;
}

void Application::DoFrame()
{

}
