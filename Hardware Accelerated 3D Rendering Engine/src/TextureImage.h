#ifndef TEXTUREIMAGE_H
#define TEXTUREIMAGE_H

//Local Includes
#include "GdiPlusManager.h"
#include "Pixel.h"

//Standard Includes
#include <cstdint>
#include <string>

class TextureImage {
public:
	TextureImage(uint32_t Width, uint32_t Height);

	TextureImage(std::wstring filename);

	TextureImage();

	~TextureImage();

	void SetPixel(const uint32_t& x, const uint32_t& y, const Pixel& p);

	const Pixel GetPixel(const uint32_t& x, const uint32_t& y) const;

	constexpr uint32_t GetWidth() const {
		return m_nImageWidth;
	}

	constexpr uint32_t GetHeight() const {
		return m_nImageHeight;
	}

	const Pixel* GetBufferPtr() const;

private:
	//Width of the image in pixels
	uint32_t m_nImageWidth = 100;
	//Hight of the image in pixels
	uint32_t m_nImageHeight = 100;

	//Real pixel data
	Pixel* m_ptrPixelData = nullptr;

	//GdiPlusManager
	GdiPlusManager m_gdiPlusManager;
};


#endif // !TEXTUREIMAGE_H
