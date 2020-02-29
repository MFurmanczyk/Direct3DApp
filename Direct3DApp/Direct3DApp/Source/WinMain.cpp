#include <sstream>
#include "../Include/WindowHeader.h"
#include "../Include/Window.h"


int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
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