#ifndef PIXEL_H
#define PIXEL_H

//Standard Includes
#include <cstdint>

struct Pixel {
	union {
		uint32_t m_nColor = 0;
		struct { uint8_t red; uint8_t green; uint8_t blue; uint8_t alpha; };
	};

	Pixel();
	Pixel(uint8_t red, uint8_t green, uint8_t blue);
	Pixel(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);
};

namespace Colours {
	static const Pixel
		WHITE(255, 255, 255, 255),
		GREY(192, 192, 192, 255),
		DARK_GREY(128, 128, 128, 255),
		VERY_DARK_GREY(64, 64, 64, 255),
		RED(255, 0, 0, 255),
		DARK_RED(128, 0, 0, 255),
		VERY_DARK_RED(64, 0, 0, 255),
		YELLOW(255, 255, 0, 255),
		DARK_YELLOW(128, 128, 0, 255),
		VERY_DARK_YELLOW(64, 64, 0, 255),
		GREEN(0, 255, 0, 255),
		DARK_GREEN(0, 128, 0, 255),
		VERY_DARK_GREEN(0, 64, 0, 255),
		CYAN(0, 255, 255, 255),
		DARK_CYAN(0, 128, 128, 255),
		VERY_DARK_CYAN(0, 64, 64, 255),
		BLUE(0, 0, 255, 255),
		DARK_BLUE(0, 0, 128, 255),
		VERY_DARK_BLUE(0, 0, 64, 255),
		MAGENTA(255, 0, 255, 255),
		DARK_MAGENTA(128, 0, 128, 255),
		VERY_DARK_MAGENTA(64, 0, 64, 255),
		BLACK(0, 0, 0, 255),
		BLANK(0, 0, 0, 0)
		;
}

#endif // !PIXEL_H
