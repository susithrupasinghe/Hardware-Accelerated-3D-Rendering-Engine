#ifndef TRANSFORMVSCBUF_H
#define TRANSFORMVSCBUF_H

//Local Includes
#include "Bindable.h"
#include "VSConstantBuffer.h"
#include "../DrawableSystem/Drawable.h"

//DirectX Includes
#include <DirectXMath.h>

class TransformVSCBuf : public Bindable {
public:
	TransformVSCBuf(const Renderer* pRenderer, const Drawable* pParent);

	virtual void Bind() const override;
private:
	const Renderer* m_pRenderer = nullptr;
	const Drawable* m_pParentDrawable = nullptr;
	mutable VSConstantBuffer<DirectX::XMMATRIX> m_vscTransformVSConstantBuf;
};

#endif // !TRANSFORMVSCBUF_H
