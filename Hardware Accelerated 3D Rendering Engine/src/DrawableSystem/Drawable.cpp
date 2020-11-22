#include "Drawable.h"

Drawable::Drawable(const Renderer* pRenderer) : m_ptrRenderer(pRenderer) {}

Drawable::~Drawable() {
	//Delete all the bindables
	for (const Bindable* pBindable : m_ptrBindables) {
		if (pBindable) delete pBindable;
	}
}

void Drawable::Draw() {
	//Bind all the bindables to the rendering pipeline
	for (const Bindable* pBindable : m_ptrBindables) {
		pBindable->Bind();
	}

	HRESULT hr = 0;
	GFX_THROW_EXCEPT_INFO_ONLY(m_ptrRenderer->pContext->DrawIndexed(m_nIndexCount, 0, 0));
}

void Drawable::AddBindable(const Bindable* pBindable) {
	m_ptrBindables.push_back(pBindable);
}

void Drawable::AddIndexBufferBindable(const IndexBuffer* pIndexBuffer) {
	m_nIndexCount = pIndexBuffer->GetElementCount();
	AddBindable(pIndexBuffer);
}
