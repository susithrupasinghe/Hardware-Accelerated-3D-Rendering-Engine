#include "VertexShader.h"

VertexShader::VertexShader(const Renderer* pRenderer, const std::wstring& shaderPath) : Bindable(pRenderer)
{
	HRESULT hr;
	//Load vertex shader to m_pVertexShaderBlob
	GFX_THROW_EXCEPT_FAILED(D3DReadFileToBlob(shaderPath.c_str(), &m_pVertexShaderBlob));

	GFX_THROW_EXCEPT_FAILED(GetDevice()->CreateVertexShader(m_pVertexShaderBlob->GetBufferPointer(), m_pVertexShaderBlob->GetBufferSize(), nullptr, &m_pVertexShader));
}

void VertexShader::Bind() const
{
	GetContext()->VSSetShader(m_pVertexShader.Get(), nullptr, 0u);
}

const void* VertexShader::GetShaderByteCodePtr() const
{
	return m_pVertexShaderBlob->GetBufferPointer();
}

const SIZE_T VertexShader::GetShaderByteCodeSize() const
{
	return m_pVertexShaderBlob->GetBufferSize();
}
