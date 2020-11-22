#ifndef DRAWTRIANGLE_H
#define DRAWTRIANGLE_H

#include "EngineBase.h"

#include <vector>
#include <cstdint>

class DrawTriangle : public EngineBase {
private:
	DrawTriangle() : EngineBase("Draw Triangle", 800, 600) {

	}

public:
	static DrawTriangle& GetSingleton() {
		return singleton;
	}

private:
	struct Vector3 { float x = 0.0f; float y = 0.0f; float z = 0.0f; };
	struct Vertex { Vector3 Position; };

	std::vector<Vertex> TriVertices = { { -0.75f, -0.75f, 0.0f }, { 0.0f, 0.75f, 0.0f }, { 0.75f, -0.75f, 0.0f } };
	std::vector<uint16_t> TriIndices = { 0, 1, 2 };

	//Triangle Vertex Buffer
	Microsoft::WRL::ComPtr<ID3D11Buffer> pTriVertexBuffer; 

	//Triangle Index BUffer
	Microsoft::WRL::ComPtr<ID3D11Buffer> pTriIndexBuffer;

	//Triangle VertexShader
	Microsoft::WRL::ComPtr<ID3D11VertexShader> pTriVertexShader;

	//Triangle Pixxel SHader
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pTriPixelShader;

	//Triangle Vertex Input Layout
	Microsoft::WRL::ComPtr<ID3D11InputLayout> pTriInputLayout;

private:
	bool OnStart() override {

		D3D11_VIEWPORT viewports[] = { {0.0f, 0.0f, (FLOAT)GetWidth(), (FLOAT)GetHeight(), 0.0f, 1.0f} };

		//Bind the viewports to the pipeline
		GetRenderer()->GetContext()->RSSetViewports((UINT)(sizeof(viewports) / sizeof(viewports[0])), viewports);

		ID3D11RenderTargetView* renderTargets[] = { GetRenderer()->GetBackbufferTargetView() };

		//Bind the backbuffer as the render target
		GetRenderer()->GetContext()->OMSetRenderTargets((UINT)(sizeof(renderTargets) / sizeof(renderTargets[0])), renderTargets, nullptr);

		HRESULT hr;

		//Craeting a vertex buffer

		D3D11_BUFFER_DESC TriVertexBufDesc = { (UINT)(TriVertices.size() * sizeof(TriVertices[0])), D3D11_USAGE::D3D11_USAGE_DEFAULT, static_cast<UINT>(D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER), (UINT)0u, (UINT)0u, (UINT)sizeof(TriVertices[0]) };

		D3D11_SUBRESOURCE_DATA TriVertexData = { (void*)TriVertices.data(), (UINT)0u, (UINT)0u };

		GFX_THROW_EXCEPT_FAILED (GetRenderer()->GetDevice()->CreateBuffer(&TriVertexBufDesc, &TriVertexData, &pTriVertexBuffer));

		//GetRenderer()->GetContext()->IASetVertexBuffers(0u, 1u, pTriVertexBuffer.GetAddressOf(), )

		//Create a Index Buffer 

		D3D11_BUFFER_DESC TriIndexBufDesc = { (UINT)(TriIndices.size() * sizeof(TriIndices[0])), D3D11_USAGE::D3D11_USAGE_DEFAULT, static_cast<UINT>(D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER), (UINT)0u, (UINT)0u, (UINT)sizeof(TriIndices[0]) };

		D3D11_SUBRESOURCE_DATA TriIndexData = { (void*)TriIndices.data(), (UINT)0u, (UINT)0u };

		GFX_THROW_EXCEPT_FAILED(GetRenderer()->GetDevice()->CreateBuffer(&TriIndexBufDesc, &TriIndexData, &pTriIndexBuffer));


		Microsoft::WRL::ComPtr<ID3DBlob> pShaderBlob;

		GFX_THROW_EXCEPT_FAILED(D3DReadFileToBlob(L"Shaders/BoxPixelShader.cso", &pShaderBlob));

		GFX_THROW_EXCEPT_FAILED(GetRenderer()->GetDevice()->CreatePixelShader(pShaderBlob->GetBufferPointer(), pShaderBlob->GetBufferSize(), nullptr, &pTriPixelShader));


		GFX_THROW_EXCEPT_FAILED ( D3DReadFileToBlob(L"Shaders/BoxVertexShader.cso", &pShaderBlob) );

		GFX_THROW_EXCEPT_FAILED(GetRenderer()->GetDevice()->CreateVertexShader(pShaderBlob->GetBufferPointer(), pShaderBlob->GetBufferSize(), nullptr, &pTriVertexShader));

		std::vector<D3D11_INPUT_ELEMENT_DESC> TriInputLayouts = { {"POSITION", 0u, DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT, 0u, 0u, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0u}, };

		GFX_THROW_EXCEPT_FAILED(GetRenderer()->GetDevice()->CreateInputLayout(TriInputLayouts.data(), (UINT)TriInputLayouts.size(), pShaderBlob->GetBufferPointer(), pShaderBlob->GetBufferSize(), &pTriInputLayout));

		return true;
	}

	bool OnUpdate(float dt) override {
		
		UINT stride = sizeof(TriVertices[0]); UINT offset = 0u;

		GetRenderer()->GetContext()->IASetVertexBuffers(0, 1, pTriVertexBuffer.GetAddressOf(), &stride, &offset);

		GetRenderer()->GetContext()->IASetIndexBuffer(pTriIndexBuffer.Get(), DXGI_FORMAT::DXGI_FORMAT_R16_UINT, 0u);

		GetRenderer()->GetContext()->IASetInputLayout(pTriInputLayout.Get());

		GetRenderer()->GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		GetRenderer()->GetContext()->VSSetShader(pTriVertexShader.Get(), nullptr, 0u);

		GetRenderer()->GetContext()->PSSetShader(pTriPixelShader.Get(), nullptr, 0u);

		GFX_THROW_EXCEPT_INFO_ONLY(GetRenderer()->GetContext()->DrawIndexed((UINT)TriIndices.size(), 0, 0));

		return true;
	}


private:
	static DrawTriangle singleton;
};

DrawTriangle DrawTriangle::singleton;

#endif // !DRAWTRIANGLE_H