#include <sstream>
#include "../Include/WindowHeader.h"
#include "../Include/Window.h"



int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	try
	{
		Window Wnd(1280, 720, "DirectX App");
		MSG Msg;
		BOOL gResult;
		while ((gResult = GetMessage(&Msg, nullptr, NULL, NULL)) > 0)
		{
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}

		if (gResult == -1)
		{
			return -1;
		}

		return Msg.wParam;
	}
	catch (const Exception & e)
	{
		MessageBox(nullptr, e.what(), e.GetType(), MB_OK | MB_ICONEXCLAMATION);
	}
	catch (std::exception & e)
	{
		MessageBox(nullptr, e.what(), "Standard exception", MB_OK | MB_ICONEXCLAMATION);
	}
	catch (...)
	{
		MessageBox(nullptr, "No details available" , "Unknown exception", MB_OK | MB_ICONEXCLAMATION);
	}
	return -1;
}