#include "InputLayout.h"

InputLayout::InputLayout(const Renderer* pRenderer, const std::vector<D3D11_INPUT_ELEMENT_DESC>& vecInputElementDescs, const VertexShader& vertexShader) : Bindable(pRenderer) {
	HRESULT hr;
	GFX_THROW_EXCEPT_FAILED(GetDevice()->CreateInputLayout(vecInputElementDescs.data(), (UINT)vecInputElementDescs.size(), vertexShader.GetShaderByteCodePtr(), vertexShader.GetShaderByteCodeSize(), &m_pInputLayout));
}

void InputLayout::Bind() const {
	GetContext()->IASetInputLayout(m_pInputLayout.Get());
}
