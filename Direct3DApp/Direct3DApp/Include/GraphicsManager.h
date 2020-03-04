#pragma once
#include "WindowHeader.h"
#include <d3d11.h>

class GraphicsManager
{
public:
	GraphicsManager(HWND hWnd);
	GraphicsManager(const GraphicsManager&) = delete;
	GraphicsManager& operator=(const GraphicsManager&) = delete;
	~GraphicsManager();
	void EndFrame();
	void ClearBuffer(float Red, float Green, float Blue) noexcept;
private:
	ID3D11Device* pDevice = nullptr;
	IDXGISwapChain* pSwapChain = nullptr;
	ID3D11DeviceContext* pContext = nullptr;
	ID3D11RenderTargetView* pTargetView = nullptr;
};