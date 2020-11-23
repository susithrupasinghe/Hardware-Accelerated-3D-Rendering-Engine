#include "Sampler.h"

Sampler::Sampler(const Renderer* pRenderer) : Bindable(pRenderer) {

	HRESULT hr;

	D3D11_SAMPLER_DESC samplerDesc = {};
	samplerDesc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;

	GFX_THROW_EXCEPT_FAILED(GetDevice()->CreateSamplerState(&samplerDesc, &pSamplerState));
}

void Sampler::Bind() const {
	GetContext()->PSSetSamplers(0, 1, pSamplerState.GetAddressOf());
}
