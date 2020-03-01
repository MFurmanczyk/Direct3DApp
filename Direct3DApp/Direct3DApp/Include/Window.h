#pragma once
#include "WindowHeader.h"
#include "../Include/Exception.h"
#include "KeyboardManager.h"
#include "MouseManager.h"

class Window
{
public:
	class WindowException : public Exception
	{
	public:
		WindowException(int pLine, const char* pFile, HRESULT hr) noexcept;
		const char* what() const noexcept override;
		virtual inline const char* GetType() const noexcept override { return "WindowException"; };
		static std::string TranslateErrorCode(HRESULT hr) noexcept;
		inline HRESULT GetErrorCode() const noexcept { return this->hr; };
		inline std::string GetErrorString() const noexcept { return TranslateErrorCode(hr); };
	private:
		HRESULT hr;
	};
private:
	class WindowClass
	{
	public:
		static const char* GetName() noexcept;
		static HINSTANCE GetInstance() noexcept;
	private:
		WindowClass() noexcept;
		~WindowClass();
		WindowClass(const WindowClass&) = delete;
		WindowClass& operator=(const WindowClass&) = delete;
		static constexpr const char* WindowClassName = "EngineWindow";
		static WindowClass WndClass;
		HINSTANCE hInstance;
	};
public:
	Window(int pWidth, int pHeight, const char* pName);
	~Window();
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
	void SetTitle(const std::string& Title); 
private:
	static LRESULT CALLBACK HandleMessageSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK HandleMessageThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT HandleMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
public:
	KeyboardManager Keyboard;
	MouseManager Mouse;
private:
	int Width;
	int Height;
	HWND hWnd;
};