#ifndef RENDERER_H
#define RENDERER_H

//Include Windows.h
#include "WindowsInclude.h"

//Include DirectX includes
#include "D3DIncludes.h"
#include <DirectXMath.h>

//Local Includes
#include "Exceptions.h"
#include "GraphicsExceptionMacros.h"
#include "DXGIInfoManager.h" // Include DXGI Info manager



class Renderer {
	friend class EngineBase;
	friend class Bindable;
	friend class Drawable;
public:
	Renderer(HWND hWnd);
	Renderer(const Renderer&) = delete;
	Renderer operator=(const Renderer&) = delete;

	void SetProjectionMatrix(const DirectX::XMMATRIX& projectionMatrix);
	const DirectX::XMMATRIX& GetProjectionMatrix() const;

public:
	
#pragma region TO_BE_DEPRECATED
	/* All the fucntions in the 'TO_BE_DEPRECATED' block is for development purposes only*/

	//Get a pointer to the ID3D11Device interface that represent the Device Object this Application created
	ID3D11Device* GetDevice() const;

	//Get a pointer to the ID3D11DeviceContext interface that represent the Immedeate Context created by D3D11CreateDeviceAndSwapChain() function
	ID3D11DeviceContext* GetContext() const;

	//Get a pointer to the ID3D11DeviceContext interface that represent the SwapChain of this application
	IDXGISwapChain* GetSwapChain() const;

	//Get a pointer to the ID3D11RenderTargetView interface that represent the back buffer of the swap chain
	ID3D11RenderTargetView* GetBackbufferTargetView() const;

#pragma endregion


public:
	//Swap backbuffer to front buffer
	void Render() const;

private:

#if defined (DEBUG) || defined (_DEBUG)
	//A reffernce to DXGIInfoManager singleton
	//static DXGIInfoManager& infoManager;
#endif

	//Pointer to ID3D11Device interface object
	Microsoft::WRL::ComPtr<ID3D11Device> pDevice;
	//Pointer to IDXGISwapchain interface object
	Microsoft::WRL::ComPtr<IDXGISwapChain> pSwapChain;
	//Pointer to ID3D11DeviceContext interface object
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> pContext;
	//Pointer to ID3D11RenderTargetView inteface of the RenderTargetView object to BackBuffer Texture. We can use this render target view to bind back buffer as our render target
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pTargetViewBackBuffer;
	//Projection Matrix if we are using a 3D view
	DirectX::XMMATRIX m_xmmatrixProjectionMatrix = {};
};

#endif // !RENDERER_H
