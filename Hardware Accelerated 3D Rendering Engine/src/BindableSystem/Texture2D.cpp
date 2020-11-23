#include "Texture2D.h"

Texture2D::Texture2D(const Renderer* pRenderer, const TextureImage& texImage) : Bindable(pRenderer) {

	HRESULT hr;

	//Create the texture

	D3D11_TEXTURE2D_DESC texture2DDesc = {};
	texture2DDesc.Width = (UINT)texImage.GetWidth();
	texture2DDesc.Height = (UINT)texImage.GetHeight();
	texture2DDesc.MipLevels = 1;
	texture2DDesc.ArraySize = 1;
	texture2DDesc.Format = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;
	texture2DDesc.SampleDesc.Count = 1;
	texture2DDesc.SampleDesc.Quality = 0;
	texture2DDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
	texture2DDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE;
	texture2DDesc.CPUAccessFlags = 0;
	texture2DDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA textureData = {};
	textureData.pSysMem = texImage.GetBufferPtr();
	textureData.SysMemPitch = texImage.GetWidth() * sizeof(Pixel);

	Microsoft::WRL::ComPtr<ID3D11Texture2D> pTexture2D;

	GFX_THROW_EXCEPT_FAILED(GetDevice()->CreateTexture2D(&texture2DDesc, &textureData, &pTexture2D));

	//Create the shader resource view on the texture
	D3D11_SHADER_RESOURCE_VIEW_DESC tex2DShaderResourceViewDesc = {};
	tex2DShaderResourceViewDesc.Format = texture2DDesc.Format;
	tex2DShaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION::D3D11_SRV_DIMENSION_TEXTURE2D;
	tex2DShaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
	tex2DShaderResourceViewDesc.Texture2D.MipLevels = 1;

	GFX_THROW_EXCEPT_FAILED(GetDevice()->CreateShaderResourceView(pTexture2D.Get(), &tex2DShaderResourceViewDesc, &pTexShaderResourceView));

	//GetDevice()->CreateTexture2D()
}

void Texture2D::Bind() const {
	GetContext()->PSSetShaderResources(0, 1, pTexShaderResourceView.GetAddressOf());
}
