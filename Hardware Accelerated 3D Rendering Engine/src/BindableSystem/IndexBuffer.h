#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H

#include "Bindable.h"

class IndexBuffer : public Bindable {
public:
	IndexBuffer(const Renderer* pRenderer, const UINT& nElementCount, const UINT& nElementSize, const DXGI_FORMAT& format, const void* pInitialData);

	virtual void Bind() const override;

	constexpr UINT GetElementCount() const {
		return m_nElementCount;
	}

private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_ptrIndexBuffer;
	DXGI_FORMAT m_format;
	UINT m_nElementCount = 0;
	UINT m_nOffset = 0;
	
};

#endif // !INDEXBUFFER_H
