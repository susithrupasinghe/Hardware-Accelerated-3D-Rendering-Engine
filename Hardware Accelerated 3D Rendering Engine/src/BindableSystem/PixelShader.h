#ifndef PIXELSHADER_H
#define PIXELSHADER_H

//Local Includes
#include "Bindable.h"

//Standard Includes
#include <string>

class PixelShader : public Bindable {
public:
	PixelShader(const Renderer* pRenderer, const std::wstring& shaderpath);

	virtual void Bind() const override;

	const void* GetShaderByteCodePtr() const;
	const SIZE_T GetShaderByteCodeSize() const;

private:
	Microsoft::WRL::ComPtr<ID3DBlob> m_pPixelShaderBlob;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pPixelShader;
};

#endif // !PIXELSHADER_H
