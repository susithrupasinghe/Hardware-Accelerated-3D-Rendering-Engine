#ifndef TEXTURE2D_H
#define TEXTURE2D_H

//Texture class responsible for creating a texture on the gpu and creating a setting its initial value
//And creating a ResourseView so we can bind it to the pipeline

//Local Includes
#include "Bindable.h"
#include "../TextureImage.h"

class Texture2D : public Bindable {
public:
	Texture2D(const Renderer* pRenderer, const TextureImage& texImage);

	virtual void Bind() const override;

private:
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> pTexShaderResourceView;
};

#endif // !TEXTURE_H
