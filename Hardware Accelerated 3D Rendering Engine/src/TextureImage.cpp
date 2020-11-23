#include "TextureImage.h"

TextureImage::TextureImage(uint32_t Width, uint32_t Height) : m_nImageWidth(Width), m_nImageHeight(Height) {
	m_ptrPixelData = new Pixel[(uint64_t)m_nImageWidth * (uint64_t)m_nImageHeight];
}

TextureImage::TextureImage(std::wstring filename) {
	Gdiplus::Bitmap bitmap(filename.c_str());
	m_nImageWidth = bitmap.GetWidth();
	m_nImageHeight = bitmap.GetHeight();

	m_ptrPixelData = new Pixel[(uint64_t)m_nImageWidth * (uint64_t)m_nImageHeight];

	const BOOL isAlpha = Gdiplus::IsAlphaPixelFormat(bitmap.GetPixelFormat());

	for (uint32_t y = 0; y < m_nImageHeight; y++) {
		for (uint32_t x = 0; x < m_nImageWidth; x++) {
			Gdiplus::Color pixel;
			bitmap.GetPixel(x, y, &pixel);

			if (isAlpha == TRUE) {
				SetPixel(x, y, Pixel(pixel.GetR(), pixel.GetG(), pixel.GetB(), pixel.GetA()));
			}
			else {
				SetPixel(x, y, Pixel(pixel.GetR(), pixel.GetG(), pixel.GetB()));
			}
		}
	}
}

TextureImage::TextureImage() : TextureImage(100, 100) {}

TextureImage::~TextureImage()
{
	if (m_ptrPixelData) delete[] m_ptrPixelData;
}

void TextureImage::SetPixel(const uint32_t& x, const uint32_t& y, const Pixel& p) {
	m_ptrPixelData[x + y * m_nImageWidth] = p;
}

const Pixel TextureImage::GetPixel(const uint32_t& x, const uint32_t& y) const {
	return m_ptrPixelData[x + y * m_nImageHeight];
}

const Pixel* TextureImage::GetBufferPtr() const {
	return m_ptrPixelData;
}
