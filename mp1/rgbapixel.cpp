#include "rgbapixel.h"

RGBAPixel::RGBAPixel()
{
	red = 0xFF;
	green = 0xFF;
	blue = 0xFF;
}
RGBAPixel::RGBAPixel(unsigned char r, unsigned char g, unsigned char b)
{
	red = r;
	green = g;
	blue = b;
}

