#include "Bindable.h"

Bindable::Bindable( const Renderer* pRenderer ) : m_ptrRenderer(pRenderer) { }

ID3D11Device* Bindable::GetDevice() const
{
	return m_ptrRenderer->pDevice.Get();
}

ID3D11DeviceContext* Bindable::GetContext() const
{
	return m_ptrRenderer->pContext.Get();
}

IDXGISwapChain* Bindable::GetSwap() const
{
	return m_ptrRenderer->pSwapChain.Get();
}
