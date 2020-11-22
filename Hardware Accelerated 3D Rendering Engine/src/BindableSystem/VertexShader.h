#ifndef VERTEXSHADER_H
#define VERTEXSHADER_H

//Local Includes
#include "Bindable.h"

//Standard Includes
#include <string>


class VertexShader : public Bindable {
public:
	VertexShader(const Renderer* pRenderer, const std::wstring& shaderPath);
	virtual void Bind() const override;
	const void* GetShaderByteCodePtr() const;
	const SIZE_T GetShaderByteCodeSize() const;

private:
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_pVertexShader;
	Microsoft::WRL::ComPtr<ID3DBlob> m_pVertexShaderBlob;
};

#endif // !VERTEXSHADER_H
