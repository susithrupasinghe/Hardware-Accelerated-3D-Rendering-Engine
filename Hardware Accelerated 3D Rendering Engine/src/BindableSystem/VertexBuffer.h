#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include "Bindable.h"

#include <cstdint>

class VertexBuffer : public Bindable {
public:
	VertexBuffer(const Renderer* pRenderer, const UINT& nElementCount, const UINT& nElementSize /* in bytes */, const void* pInitialData);

	virtual void Bind() const override;

private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_ptrVertexBuffer;
	UINT m_nStride = 0u;
	UINT m_nOffset = 0u;
};

#endif // !VERTEXBUFFER_H
