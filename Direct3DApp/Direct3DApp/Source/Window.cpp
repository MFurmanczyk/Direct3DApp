#include "../Include/Window.h"
#include <sstream>
#include "../resource.h"

Window::WindowClass Window::WindowClass::WndClass;

const char* Window::WindowClass::GetName() noexcept
{
	return WindowClassName;
}

HINSTANCE Window::WindowClass::GetInstance() noexcept
{
	return WndClass.hInstance;
}

Window::WindowClass::WindowClass() noexcept
	: hInstance(GetModuleHandle(nullptr))
{
	WNDCLASSEX wc{ 0 };
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = HandleMessageSetup;
	wc.cbClsExtra = NULL;
	wc.cbWndExtra = NULL;
	wc.hInstance = GetInstance();
	wc.hIcon = static_cast<HICON>(LoadImage(hInstance, MAKEINTRESOURCE(IDI_APPICON), IMAGE_ICON, 32, 32, 0));
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = GetName();
	wc.hIconSm = static_cast<HICON>(LoadImage(hInstance, MAKEINTRESOURCE(IDI_APPICON), IMAGE_ICON, 16, 16, 0));;
	RegisterClassEx(&wc);
}

Window::WindowClass::~WindowClass()
{
	UnregisterClass(WindowClassName, GetInstance());
}

Window::Window(int pWidth, int pHeight, const char* pName) 
{
	RECT wr;
	wr.left = 100;
	wr.right = pWidth + wr.left;
	wr.top = 100;
	wr.bottom = pHeight + wr.top;
	if (AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE) == 0)
	{
		throw WindowException(__LINE__, __FILE__, GetLastError());
	}

	hWnd = CreateWindow(WindowClass::GetName(), pName,
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT, wr.right - wr.left, wr.bottom - wr.top,
		nullptr, nullptr, WindowClass::GetInstance(), this);

	if (hWnd == nullptr)
	{
		throw WindowException(__LINE__, __FILE__, GetLastError());
	}

	ShowWindow(hWnd, SW_SHOWDEFAULT);
	//GraphicsManager object
	pGraphics = std::make_unique<GraphicsManager>(hWnd);
}

Window::~Window()
{
	DestroyWindow(hWnd);
}

void Window::SetTitle(const std::string& Title)
{
	if (SetWindowText(hWnd, Title.c_str()) == 0) 
	{
		throw Window::WindowException(__LINE__, __FILE__, GetLastError());
	}
}

std::optional<int> Window::ProcessMessage()
{
	MSG Message;
	while (PeekMessage(&Message, nullptr, NULL, NULL, PM_REMOVE))
	{
		if (Message.message == WM_QUIT)
		{
			return Message.wParam;
		}
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return std::optional<int>();
}

GraphicsManager& Window::Graphics()
{
	return *pGraphics;
}

LRESULT WINAPI Window::HandleMessageSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_NCCREATE)
	{
		//extract pointer to window class form creation data
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		Window* const pWindow = static_cast<Window*>(pCreate->lpCreateParams);
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWindow));
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::HandleMessageThunk));
		return pWindow->HandleMessage(hWnd, msg, wParam, lParam);
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT WINAPI Window::HandleMessageThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	Window* const pWindow = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	return pWindow->HandleMessage(hWnd, msg, wParam, lParam);
}

LRESULT Window::HandleMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	switch (msg)
	{
		//Processing messages
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
	case WM_KILLFOCUS:
		Keyboard.ClearState();
		break;
	//Keyboard messages
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
		if(!(lParam & 0x40000000) || Keyboard.IsAutorepeatEnabled())
		Keyboard.OnKeyPressed(static_cast<unsigned char>(wParam));
		break;
	case WM_KEYUP:
	case WM_SYSKEYUP:
		Keyboard.OnKeyReleased(static_cast<unsigned char>(wParam));
		break;
	case WM_CHAR:
		Keyboard.OnChar(static_cast<unsigned char>(wParam));
		break;
		//Mouse messages
	case WM_MOUSEMOVE:
	{
		POINTS Points = MAKEPOINTS(lParam);
		if (Points.x >= 0 && Points.x < Width && Points.y >= 0 && Points.y < Height)
		{
			Mouse.OnMouseMove(Points.x, Points.y);
			if (!Mouse.IsInWindow())
			{
				SetCapture(hWnd);
				Mouse.OnMouseEnter();
			}
			else
			{
				if (wParam & (MK_LBUTTON | MK_RBUTTON))
				{
					Mouse.OnMouseMove(Points.x, Points.y);
				}
				else
				{
					ReleaseCapture();
					Mouse.OnMouseLeave();
				}
			}
		}

		break;
	}
	case WM_LBUTTONDOWN:
	{
		POINTS Points = MAKEPOINTS(lParam);
		Mouse.OnLeftPressed(Points.x, Points.y);
		break;
	}
	case WM_RBUTTONDOWN:
	{
		POINTS Points = MAKEPOINTS(lParam);
		Mouse.OnRightPressed(Points.x, Points.y);
		break;
	}
	case WM_LBUTTONUP:
	{
		POINTS Points = MAKEPOINTS(lParam);
		Mouse.OnLeftReleased(Points.x, Points.y);
		break;
	}
	case WM_RBUTTONUP:
	{
		POINTS Points = MAKEPOINTS(lParam);
		Mouse.OnRightReleased(Points.x, Points.y);
		break;
	}
	case WM_MOUSEWHEEL:
	{
		POINTS Points = MAKEPOINTS(lParam);
		if (GET_WHEEL_DELTA_WPARAM(wParam) > 0)
		{
			Mouse.OnWheelUp(Points.x, Points.y);
		}
		else if (GET_WHEEL_DELTA_WPARAM(wParam) > 0)
		{
			Mouse.OnWheelDown(Points.x, Points.y);
		}
		break;
	}
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

///Window exception code
Window::WindowException::WindowException(int pLine, const char* pFile, HRESULT hr) noexcept
	: Exception(pLine, pFile), hr(hr)
{

}

const char* Window::WindowException::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl
		<< "[Error code] " << GetErrorCode() << std::endl
		<< "[Description] " << GetErrorString() << std::endl
		<< GetOriginString();
	WhatBuffer = oss.str();
	return WhatBuffer.c_str();
}

std::string Window::WindowException::TranslateErrorCode(HRESULT hr) noexcept
{
	char* pMessageBuffer = nullptr;
	DWORD nMessageLength = FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER
		| FORMAT_MESSAGE_FROM_SYSTEM
		| FORMAT_MESSAGE_IGNORE_INSERTS,
		nullptr,
		hr,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		reinterpret_cast<LPSTR> (&pMessageBuffer),
		NULL,
		nullptr
	);
	if (nMessageLength == 0)
	{
		return "Unidentifier error code";
	}
	std::string ErrorString = pMessageBuffer;
	LocalFree(pMessageBuffer);
	return ErrorString;
}