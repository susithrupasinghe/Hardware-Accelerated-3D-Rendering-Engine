#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(const Renderer* pRenderer, const UINT& nElementCount, const UINT& nElementSize, const DXGI_FORMAT& format, const void* pInitialData) : Bindable(pRenderer), m_format(format), m_nElementCount(nElementCount) ,m_nOffset(0u) {
	//Initialize a D3D11_BUFFER_DESC for index buffer according to the given index buffer information
	D3D11_BUFFER_DESC indexBufferDesc = { (UINT)(m_nElementCount * nElementSize), D3D11_USAGE::D3D11_USAGE_DEFAULT, static_cast<UINT>(D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER), (UINT)0u, (UINT)0u, (UINT)nElementSize };
	D3D11_SUBRESOURCE_DATA indexBufData = { pInitialData, (UINT)0u, (UINT)0u };
	HRESULT hr;
	GFX_THROW_EXCEPT_FAILED(GetDevice()->CreateBuffer(&indexBufferDesc, &indexBufData, &m_ptrIndexBuffer));
}

void IndexBuffer::Bind() const {
	GetContext()->IASetIndexBuffer(m_ptrIndexBuffer.Get(), m_format, m_nOffset);
}
