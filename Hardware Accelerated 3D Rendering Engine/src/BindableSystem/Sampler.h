#ifndef SAMPLER_H
#define SAMPLER_H

//Sampler class responsible for telling the pipeline how to use the bound texture

//Local Includes
#include "Bindable.h"

class Sampler : public Bindable {
public:
	Sampler(const Renderer* pRenderer);

	virtual void Bind() const override;

private:
	Microsoft::WRL::ComPtr<ID3D11SamplerState> pSamplerState;
};

#endif // !SAMPLER_H
