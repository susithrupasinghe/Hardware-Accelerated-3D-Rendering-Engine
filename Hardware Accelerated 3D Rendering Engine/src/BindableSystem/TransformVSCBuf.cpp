#include "TransformVSCBuf.h"

TransformVSCBuf::TransformVSCBuf(const Renderer* pRenderer, const Drawable* pParent)
	:
	m_pRenderer(pRenderer),
	Bindable(pRenderer),
	m_vscTransformVSConstantBuf(pRenderer, DirectX::XMMatrixIdentity()),
	m_pParentDrawable(pParent)
{

}

void TransformVSCBuf::Bind() const {
	m_vscTransformVSConstantBuf.GetBuffer() = DirectX::XMMatrixTranspose(
		m_pParentDrawable->GetTransform() * m_pRenderer->GetProjectionMatrix()
	);
	m_vscTransformVSConstantBuf.Update();
	m_vscTransformVSConstantBuf.Bind();
}
