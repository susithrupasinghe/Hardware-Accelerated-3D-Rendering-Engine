#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const Renderer* pRenderer, const UINT& nElementCount, const UINT& nElementSize, const void* pInitialData) : Bindable(pRenderer), m_nStride(nElementSize), m_nOffset(0u)
{
	D3D11_BUFFER_DESC vertexBufferDesc = { (UINT)(nElementCount * nElementSize), D3D11_USAGE::D3D11_USAGE_DEFAULT, static_cast<UINT>(D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER), (UINT)0u, (UINT)0u, (UINT)nElementSize };
	D3D11_SUBRESOURCE_DATA vertexBufData = { pInitialData, (UINT)0u, (UINT)0u };

	HRESULT hr;
	GFX_THROW_EXCEPT_FAILED(GetDevice()->CreateBuffer(&vertexBufferDesc, &vertexBufData, &m_ptrVertexBuffer));
}

void VertexBuffer::Bind() const {
	GetContext()->IASetVertexBuffers(0u, 1, m_ptrVertexBuffer.GetAddressOf(), &m_nStride, &m_nOffset);
}
