#ifndef INPUTLAYOUT_H
#define INPUTLAYOUT_H

//Local Includes
#include "Bindable.h"
#include "VertexShader.h"

//Standard Includes
#include <vector>

class InputLayout : public Bindable {
public:
	InputLayout(const Renderer* pRenderer, const std::vector<D3D11_INPUT_ELEMENT_DESC>& vecInputElementDescs, const VertexShader& vertexShader);

	virtual void Bind() const override;

	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_pInputLayout;
};

#endif // !INPUTLAYOUT_H
