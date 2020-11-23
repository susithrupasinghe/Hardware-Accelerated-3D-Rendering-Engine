#include "Pixel.h"

Pixel::Pixel() : red(0), green(0), blue(0), alpha(255)
{
}

Pixel::Pixel(uint8_t red, uint8_t green, uint8_t blue) : red(red), green(green), blue(blue), alpha(255)
{
}

Pixel::Pixel(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) : red(red), green(green), blue(blue), alpha(alpha)
{
}