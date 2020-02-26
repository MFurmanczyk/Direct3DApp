#include <Windows.h>

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	const auto pClassName = "DirectX App";

	//register window class
	WNDCLASSEX wc{ 0 };
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = DefWindowProc;
	wc.cbClsExtra = NULL;
	wc.cbWndExtra = NULL;
	wc.hInstance = hInstance;
	wc.hIcon = nullptr;
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = pClassName;
	RegisterClassEx(&wc);

	//create window instance
	HWND hWnd = CreateWindowExA(
		NULL,
		pClassName,
		"DirectX App",
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		200, 
		200,
		1280,
		720,
		nullptr,
		nullptr, 
		hInstance,
		nullptr
	);

	ShowWindow(hWnd, SW_SHOW);
	while (true);
	return 0;
}