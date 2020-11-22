#include "Triangle.h"

Triangle::Triangle(const Renderer* pRenderer) : Drawable(pRenderer) {
	AddBindable(new VertexBuffer(GetRenderer(), (UINT)m_vecVertices.size(), (UINT)sizeof(m_vecVertices[0]), m_vecVertices.data()));
	AddIndexBufferBindable(new IndexBuffer(GetRenderer(), (UINT)m_vecIndices.size(), (UINT)sizeof(m_vecIndices[0]), DXGI_FORMAT::DXGI_FORMAT_R16_UINT, m_vecIndices.data()));
	const VertexShader* pVertexShader = new VertexShader(GetRenderer(), std::wstring(L"Shaders/BoxVertexShader.cso"));
	AddBindable(pVertexShader);
	AddBindable(new PixelShader(GetRenderer(), std::wstring(L"Shaders/BoxPixelShader.cso")));
	std::vector<D3D11_INPUT_ELEMENT_DESC> TriInputLayouts = { { "POSITION", 0u, DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT, 0u, 0u, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0u }, };
	AddBindable(new InputLayout(GetRenderer(), TriInputLayouts, *pVertexShader));
	AddBindable(new PrimitiveTopology(GetRenderer(), D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
}
