#include <Windows.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		//Processing messages
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	const auto pClassName = "DirectX App";

	//register window class
	WNDCLASSEX wc{ 0 };
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc;
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
	
	MSG msg;
	BOOL gResult;
	while ((gResult = GetMessage(&msg, nullptr, NULL, NULL)) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	if (gResult == -1)
	{
		return -1;
	}
	else
	{
		return msg.wParam;
	}
}