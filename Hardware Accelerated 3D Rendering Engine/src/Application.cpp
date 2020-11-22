#include "Application.h"

Application Application::singleton;

Application::Application() : EngineBase("3D Rendering Engine", 800, 600) {

}

Application& Application::GetSingleton()
{
	return singleton;
}

bool Application::OnStart() {
	D3D11_VIEWPORT viewports[1] = {
	{0.0f, 0.0f, (FLOAT)GetWidth(), (FLOAT)GetHeight(), 0.0f, 1.0f}
	};

	//Bind the viewports to the pipeline
	GetRenderer()->GetContext()->RSSetViewports((UINT)(sizeof(viewports) / sizeof(viewports[0])), viewports);

	ID3D11RenderTargetView* renderTargets[1] = {
		GetRenderer()->GetBackbufferTargetView()
	};

	//Bind the backbuffer as the render target
	GetRenderer()->GetContext()->OMSetRenderTargets((UINT)(sizeof(renderTargets) / sizeof(renderTargets[0])), renderTargets, nullptr);

	HRESULT hr;


	/*
	typedef struct D3D11_BUFFER_DESC
    {
    UINT ByteWidth;
    D3D11_USAGE Usage;
    UINT BindFlags;
    UINT CPUAccessFlags;
    UINT MiscFlags;
    UINT StructureByteStride;
    } 	D3D11_BUFFER_DESC;	
	*/


	//Create a VertexBuffer

	D3D11_BUFFER_DESC BoxVertexBufferDesc = { (UINT)(boxVertices.size() * sizeof(Vertex)), D3D11_USAGE::D3D11_USAGE_DEFAULT, static_cast<UINT>(D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER), (UINT)0u, (UINT)0u, (UINT)sizeof(Vertex) };
	
	D3D11_SUBRESOURCE_DATA BoxVertexData = { static_cast<void*>(boxVertices.data()), (UINT)0u, (UINT)0u };

	GFX_THROW_EXCEPT_FAILED( GetRenderer()->GetDevice()->CreateBuffer(&BoxVertexBufferDesc, &BoxVertexData, &pBoxVertexBuffer));

	//Create a Index Buffer

	D3D11_BUFFER_DESC BoxIndexBufferDesc = { (UINT)(boxIndices.size() * sizeof(uint16_t)), D3D11_USAGE::D3D11_USAGE_DEFAULT, static_cast<UINT>(D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER), (UINT)0u, (UINT)0u, (UINT)sizeof(uint16_t) };

	D3D11_SUBRESOURCE_DATA BoxIndexData = { static_cast<void*>(boxIndices.data()), (UINT)0u, (UINT)0u };

	GFX_THROW_EXCEPT_FAILED(GetRenderer()->GetDevice()->CreateBuffer(&BoxIndexBufferDesc, &BoxIndexData, &pBoxIndexBuffer));

	//Load Pixel Shader to the 

	GFX_THROW_EXCEPT_FAILED(D3DReadFileToBlob(L"Shaders/BoxPixelShader.cso", &pShaderBlob));

	GFX_THROW_EXCEPT_FAILED(GetRenderer()->GetDevice()->CreatePixelShader(pShaderBlob->GetBufferPointer(), pShaderBlob->GetBufferSize(), nullptr, &pBoxPixelShader));
	
	//Load Vertex Shader

	GFX_THROW_EXCEPT_FAILED(D3DReadFileToBlob(L"Shaders/BoxVertexShader.cso", &pShaderBlob));

	GFX_THROW_EXCEPT_FAILED(GetRenderer()->GetDevice()->CreateVertexShader(pShaderBlob->GetBufferPointer(), pShaderBlob->GetBufferSize(), nullptr, &pBoxVertexShader));

	//Create Input Layout
	const std::vector<D3D11_INPUT_ELEMENT_DESC> InputElementsDesc = {
		{"POSITION", 0u, DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

	GFX_THROW_EXCEPT_FAILED(
		GetRenderer()->GetDevice()->CreateInputLayout(InputElementsDesc.data(), (UINT)InputElementsDesc.size(), pShaderBlob->GetBufferPointer(), pShaderBlob->GetBufferSize(), &pBoxInputLayout)
	);

	D3D11_BUFFER_DESC BoxVertexShaderConstantBufferDesc = { (UINT) sizeof(DirectX::XMMATRIX), D3D11_USAGE::D3D11_USAGE_DYNAMIC, static_cast<UINT>(D3D11_BIND_FLAG::D3D11_BIND_CONSTANT_BUFFER), static_cast<UINT>(D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE), (UINT)0u, (UINT)0u };

	GFX_THROW_EXCEPT_FAILED(GetRenderer()->GetDevice()->CreateBuffer(&BoxVertexShaderConstantBufferDesc, nullptr, &pBoxPixelShaderConstantBuffer));

	return true;
}

bool Application::OnUpdate(float dt) {

	UINT stride = sizeof(Vertex);
	UINT offset = 0u;

	GetRenderer()->GetContext()->IASetVertexBuffers(0, 1, pBoxVertexBuffer.GetAddressOf(), &stride, &offset);

	GetRenderer()->GetContext()->IASetIndexBuffer(pBoxIndexBuffer.Get(), DXGI_FORMAT::DXGI_FORMAT_R16_UINT, 0);

	GetRenderer()->GetContext()->IASetInputLayout(pBoxInputLayout.Get());

	GetRenderer()->GetContext()->VSSetShader(pBoxVertexShader.Get(), nullptr, 0);

	GetRenderer()->GetContext()->PSSetShader(pBoxPixelShader.Get(), nullptr, 0);

	GetRenderer()->GetContext()->VSSetConstantBuffers(0, 1, pBoxVertexShaderConstantBuffer.GetAddressOf());

	GetRenderer()->GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	GFX_THROW_EXCEPT_INFO_ONLY( GetRenderer()->GetContext()->DrawIndexed((UINT)boxIndices.size(), 0, 0));

	return true;
}
