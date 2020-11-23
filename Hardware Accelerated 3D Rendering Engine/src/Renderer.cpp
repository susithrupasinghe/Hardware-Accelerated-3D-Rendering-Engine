#include "Renderer.h"

//In Direct3D11 before we do anything we have to do some initialing stuff
//First we have to create a Direct3D Device object on API Side and get an interface to that object (ID3D11Device) 
//Device object represent the physical device (the GPU) you choose to run your D3D pipeline
//We can use that ID3D11Device interface to allocate resources on that device for your application
//Then there is DEvice Context. We need to quary ID3D11Device object to get a interface to ID3D11DeviceContext.
//Device Context represent the allocated resources and our Direct3D pipeline on that Device.
//I think we only allow to have only one device context per device and a device context can only represent single device
//(Because we do not craete an actual physical device. Physical device is already there we just create an object that represent 
//that device and get an Interface for that object. And also we realy don't create a device context. Context is already there 
//We just get an interface to that object)

Renderer::Renderer(HWND hWnd) {
	//When we create any kind of a resource in Direct3D, we have to explicitly tell the API how to configure those resources. 
//The way we do that is by parsing those descriptor structs to those specific functions.

//Here we are parsing a DXGI_SWAP_CHAIN_DESC descriptor struct to  	D3D11CreateDeviceAndSwapChain() function to tell the API how to configure the swap chain we want to create.

//Create DXGI_SWAP_CHAIN_DESC to configure our swap chain
//According to the https://docs.microsoft.com/en-us/windows/win32/api/dxgi/ns-dxgi-dxgi_swap_chain_desc
//DXGI_SWAP_CHAIN_DESC contains
//DXGI_MODE_DESC BufferDesc - A DXGI_MODE_DESC structure that describes the backbuffer display mode
	//DXGI_MODE_DESC contains (https://docs.microsoft.com/en-us/previous-versions/windows/desktop/legacy/bb173064(v=vs.85))
		//UINT Width - A value that describes the resolution width. If you specify the width as zero when you call the IDXGIFactory::CreateSwapChain method to create a swap chain, the runtime obtains the width from the output window and assigns this width value to the swap-chain description. You can subsequently call the IDXGISwapChain::GetDesc method to retrieve the assigned width value
		//UINT Height - A value describing the resolution height. If you specify the height as zero when you call the IDXGIFactory::CreateSwapChain method to create a swap chain, the runtime obtains the height from the output window and assigns this height value to the swap-chain description. You can subsequently call the IDXGISwapChain::GetDesc method to retrieve the assigned height value.
		//DXGI_RATIONAL RefreshRate - A DXGI_RATIONAL structure describing the refresh rate in hertz
			//DXGI_RATIONAL contains (https://docs.microsoft.com/en-us/windows/win32/api/dxgicommon/ns-dxgicommon-dxgi_rational?redirectedfrom=MSDN)
				//UINT Numerator - An unsigned integer value representing the top of the rational number
				//UINT Denominator - An unsigned integer value representing the bottom of the rational number

				//The DXGI_RATIONAL structure operates under the following rules :
					//1. 0 / 0 is legal and will be interpreted as 0 / 1.
					//2. 0 / anything is interpreted as zero.
					//If you are representing a whole number, the denominator should be 1.


		//DXGI_FORMAT Format - A DXGI_FORMAT structure describing the display format.
		//DXGI_MODE_SCANLINE_ORDER ScanlineOrdering - A member of the DXGI_MODE_SCANLINE_ORDER enumerated type describing the scanline drawing mode.
		//DXGI_MODE_SCALING Scaling - A member of the DXGI_MODE_SCALING enumerated type describing the scaling mode.

//DXGI_SAMPLE_DESC SampleDesc - A DXGI_SAMPLE_DESC structure that describes multi-sampling parameters
	//DXGI_SAMPLE_DESC contains (https://docs.microsoft.com/en-us/windows/win32/api/dxgicommon/ns-dxgicommon-dxgi_sample_desc)
		//UINT Count - The number of multisamples per pixel.
		//UINT Quality - The image quality level. The higher the quality, the lower the performance. The valid range is between zero and one less than the level returned by ID3D10Device::CheckMultisampleQualityLevels for Direct3D 10 or ID3D11Device::CheckMultisampleQualityLevels for Direct3D 11.
		//For Direct3D 10.1 and Direct3D 11, you can use two special quality level values.

//DXGI_USAGE BufferUsage - A member of the DXGI_USAGE enumerated type that describes the surface usage and CPU access options for the back buffer.The back buffer can be used for shader input or render - target output
//UINT BufferCount - A value that describes the number of buffers in the swap chain. When you call IDXGIFactory::CreateSwapChain to create a full-screen swap chain, you typically include the front buffer in this value. For more information about swap-chain buffers, see Remarks.
//HWND OutputWindow - An HWND handle to the output window. This member must not be NULL
//BOOL Windowed - A Boolean value that specifies whether the output is in windowed mode. TRUE if the output is in windowed mode; otherwise, FALSE
//DXGI_SWAP_EFFECT SwapEffect - A member of the DXGI_SWAP_EFFECT enumerated type that describes options for handling the contents of the presentation buffer after presenting a surface
//DXGI_SWAP_CHAIN_FLAG Flags - A member of the DXGI_SWAP_CHAIN_FLAG enumerated type that describes options for swap-chain behavior




	DXGI_SWAP_CHAIN_DESC swap_chain_desc = {};
	// If we set Width and Height to 0 API will automaticaly choose the width and height from hWnd we give this descriptor
	swap_chain_desc.BufferDesc.Width = 0;
	swap_chain_desc.BufferDesc.Height = 0;
	swap_chain_desc.BufferDesc.Format = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;
	//Set RefreshRate.Numerator and RefreshRate.Denominator to 0. Which basicly means api will choose default refresh rate
	swap_chain_desc.BufferDesc.RefreshRate.Numerator = 0;
	swap_chain_desc.BufferDesc.RefreshRate.Denominator = 0;
	//Set BufferDesc.Scaling to DXGI_MODE_SCALING::DXGI_MODE_SCALING_UNSPECIFIED and BufferDesc.ScanlineOrdering to DXGI_MODE_SCANLINE_ORDER::DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED to tell api to choose default settings
	swap_chain_desc.BufferDesc.Scaling = DXGI_MODE_SCALING::DXGI_MODE_SCALING_UNSPECIFIED;
	swap_chain_desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER::DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	//We don't need any multisampling
	swap_chain_desc.SampleDesc.Count = 1;
	swap_chain_desc.SampleDesc.Quality = 0;
	//We are using swap chain to render it to render target
	swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	//Since we are using windowed mode front buffer will be created automaticaly. So we only need one additional buffer besides front buffer as our back buffer
	swap_chain_desc.BufferCount = 1;
	swap_chain_desc.OutputWindow = hWnd;
	swap_chain_desc.Windowed = TRUE;
	swap_chain_desc.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_DISCARD;
	//We are not using any flags for now
	swap_chain_desc.Flags = 0;

	UINT nDeviceCreationFlags = 0;

#if defined(DEBUG) || defined(_DEBUG)
	nDeviceCreationFlags |= D3D11_CREATE_DEVICE_FLAG::D3D11_CREATE_DEVICE_DEBUG;
#endif

	//Craete device and swap chain and immediate device context
	HRESULT hr;
	GFX_THROW_EXCEPT_FAILED(
		//call D3D11CreateDeviceAndSwapChain() to create ID3D11Device object and ID3D11DeviceContext object and Swap chain 
		D3D11CreateDeviceAndSwapChain(
			nullptr /*Pointer to a IDXGIAdapter interface object. Parse it nullptr to tell the api to choose the first adapter returns from EnmumerateAdapters() function*/,
			D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE,
			nullptr /*We are not using software model*/,
			nDeviceCreationFlags,
			nullptr /*pointer to a D3D_FEATURE_LEVEL array requested by user. Parse it nullptr to choose highest feature level available in this sdk version*/,
			0,
			D3D11_SDK_VERSION,
			&swap_chain_desc,
			&pSwapChain,
			&pDevice,
			nullptr,
			&pContext
		)
	);

	//Device, Swap Chain and Immideate Context has been created successfully

	//Get the ID3D11Resource interface to the backbuffer of the swapchain
	Microsoft::WRL::ComPtr<ID3D11Resource> pBackBufferResource;

	//Quary for ID3D11resource interface on Back buffer of the swap chain
	//IDXGISwapChain::GetBuffer() function does that for us
	GFX_THROW_EXCEPT_FAILED(pSwapChain->GetBuffer(0, __uuidof(ID3D11Resource), &pBackBufferResource));

	//D3D11_RENDER_TARGET_VIEW_DESC backbufferRenderTargetDesc = {};

	//Create a render target view for backbuffer and store a pointer to the ID3D11RenderTarget Interface in pTargetViewBackBuffer
	GFX_THROW_EXCEPT_FAILED(pDevice->CreateRenderTargetView(pBackBufferResource.Get(), nullptr, &pTargetViewBackBuffer));

	//Apperantly ID3D11Device::CreateRenderTargetView() function doesn't require D3D11_RENDER_TARGET_VIEW_DESC. We can just parse nullptr for that 
	// TODO : Search why ID3D11Device::CreateRenderTargetView() function doesn't require D3D11_RENDER_TARGET_VIEW_DESC

	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> pDepthStencilState;

	D3D11_DEPTH_STENCIL_DESC depthStencilDesc = {};
	depthStencilDesc.DepthEnable = TRUE;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
	depthStencilDesc.StencilEnable = FALSE;

	//Create Depth Stencil State
	GFX_THROW_EXCEPT_FAILED(pDevice->CreateDepthStencilState(&depthStencilDesc, &pDepthStencilState));

	//Set Depth Stencil State to the pipline
	pContext->OMSetDepthStencilState(pDepthStencilState.Get(), 1u);


	//Create the Depth Stencil Texture
	Microsoft::WRL::ComPtr<ID3D11Texture2D> pDepthStencilTex;

	D3D11_TEXTURE2D_DESC depthStencilTexDesc = {};
	depthStencilTexDesc.Width = 800;
	depthStencilTexDesc.Height = 600;
	depthStencilTexDesc.MipLevels = 1;
	depthStencilTexDesc.ArraySize = 1;
	depthStencilTexDesc.Format = DXGI_FORMAT::DXGI_FORMAT_D32_FLOAT;
	depthStencilTexDesc.SampleDesc.Count = 1;
	depthStencilTexDesc.SampleDesc.Quality = 0;
	depthStencilTexDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
	depthStencilTexDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL;

	GFX_THROW_EXCEPT_FAILED(pDevice->CreateTexture2D(&depthStencilTexDesc, nullptr, &pDepthStencilTex));

	//Create Depth Stencil View 
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc = {};
	depthStencilViewDesc.Format = DXGI_FORMAT::DXGI_FORMAT_D32_FLOAT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION::D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	GFX_THROW_EXCEPT_FAILED(pDevice->CreateDepthStencilView(pDepthStencilTex.Get(), &depthStencilViewDesc, &pDepthStencilView));

}

void Renderer::ClearBackBuffer(const DirectX::XMFLOAT4& color) {
	pContext->ClearRenderTargetView(pTargetViewBackBuffer.Get(), (FLOAT*)(&color));
	pContext->ClearDepthStencilView(pDepthStencilView.Get(), D3D11_CLEAR_FLAG::D3D11_CLEAR_DEPTH, 1.0f, 0);

}

void Renderer::SetProjectionMatrix(const DirectX::XMMATRIX& projectionMatrix)
{
	m_xmmatrixProjectionMatrix = projectionMatrix;
}

const DirectX::XMMATRIX& Renderer::GetProjectionMatrix() const
{
	return m_xmmatrixProjectionMatrix;
}

ID3D11Device* Renderer::GetDevice() const
{
	return pDevice.Get();
}

ID3D11DeviceContext* Renderer::GetContext() const
{
	return pContext.Get();
}

IDXGISwapChain* Renderer::GetSwapChain() const
{
	return pSwapChain.Get();
}

ID3D11RenderTargetView* Renderer::GetBackbufferTargetView() const
{
	return pTargetViewBackBuffer.Get();
}

//Get a pointer to ID3D11DepthStencilView interface of the DepthStencilView object to the backbuffer

ID3D11DepthStencilView* Renderer::GetDepthStencilView() const {
	return pDepthStencilView.Get();
}

void Renderer::Render() const
{
	HRESULT hr;
#if defined (DEBUG) || defined (_DEBUG)
	g_DXGIInfoManager.Set();
#endif
	if (FAILED(hr = pSwapChain->Present(0, 0))) {
		if (hr == DXGI_ERROR_DEVICE_REMOVED) {
			throw GFX_EXCEPT_DEVICE_REMOVED(pDevice->GetDeviceRemovedReason());
		}
		else {
			throw GFX_EXCEPT_WIN(hr);
			
		}
	}
}
