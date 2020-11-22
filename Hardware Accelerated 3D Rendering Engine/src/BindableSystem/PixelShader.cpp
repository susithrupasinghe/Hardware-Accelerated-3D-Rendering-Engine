#include "PixelShader.h"

PixelShader::PixelShader(const Renderer* pRenderer, const std::wstring& shaderpath) : Bindable(pRenderer) {
	HRESULT hr;

	//Load Shader file
	GFX_THROW_EXCEPT_FAILED(D3DReadFileToBlob(shaderpath.c_str(), &m_pPixelShaderBlob));

	GFX_THROW_EXCEPT_FAILED(GetDevice()->CreatePixelShader(m_pPixelShaderBlob->GetBufferPointer(), m_pPixelShaderBlob->GetBufferSize(), nullptr, &m_pPixelShader));
}
 
void PixelShader::Bind() const {
	//Bind the pixel shader to the pipeline
	GetContext()->PSSetShader(m_pPixelShader.Get(), nullptr, 0u);
}

const void* PixelShader::GetShaderByteCodePtr() const {
	return m_pPixelShaderBlob->GetBufferPointer();
}

const SIZE_T PixelShader::GetShaderByteCodeSize() const {
	return m_pPixelShaderBlob->GetBufferSize();
}
