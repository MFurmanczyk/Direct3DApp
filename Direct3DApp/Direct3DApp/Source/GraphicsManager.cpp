#include "..\Include\GraphicsManager.h"

#pragma comment(lib, "d3d11.lib")

GraphicsManager::GraphicsManager(HWND hWnd)
{
	DXGI_SWAP_CHAIN_DESC SwapChainDescriptor = {};
	SwapChainDescriptor.BufferDesc.Width = 0;
	SwapChainDescriptor.BufferDesc.Height = 0;
	SwapChainDescriptor.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	SwapChainDescriptor.BufferDesc.RefreshRate.Numerator = 0;
	SwapChainDescriptor.BufferDesc.RefreshRate.Denominator = 0;
	SwapChainDescriptor.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	SwapChainDescriptor.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	SwapChainDescriptor.SampleDesc.Count = 1;
	SwapChainDescriptor.SampleDesc.Quality = 0;
	SwapChainDescriptor.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	SwapChainDescriptor.BufferCount = 1;
	SwapChainDescriptor.OutputWindow = hWnd;
	SwapChainDescriptor.Windowed = TRUE;
	SwapChainDescriptor.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	SwapChainDescriptor.Flags = 0;

	D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		NULL,
		nullptr,
		NULL,
		D3D11_SDK_VERSION,
		&SwapChainDescriptor,
		&pSwapChain,
		&pDevice,
		nullptr,
		&pContext
	);

	//access to BackBuffer
	ID3D11Resource* pBackBuffer = nullptr;
	pSwapChain->GetBuffer(0, __uuidof(ID3D11Resource), reinterpret_cast<void**>(&pBackBuffer));
	pDevice->CreateRenderTargetView(
		pBackBuffer,
		nullptr,
		&pTargetView
	);
	pBackBuffer->Release();
}

GraphicsManager::~GraphicsManager()
{
	if (pDevice)
	{
		pDevice->Release();
	}
	if (pSwapChain)
	{
		pSwapChain->Release();
	}
	if (pContext)
	{
		pContext->Release();
	}
}

void GraphicsManager::EndFrame()
{
	pSwapChain->Present(1u, NULL);
}

void GraphicsManager::ClearBuffer(float Red, float Green, float Blue) noexcept
{
	const float Color[] = { Red, Green, Blue, 1.f };
	pContext->ClearRenderTargetView(pTargetView, Color);
}
