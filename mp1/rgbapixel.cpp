#include "rgbapixel.h"

RGBAPixel::RGBAPixel() {
	this->alpha = 255;
	this->red = 255;
	this->green = 255;
	this->blue = 255;
}


RGBAPixel::RGBAPixel(uint8_t r, uint8_t g, uint8_t b) {
	this->alpha = 255;
	this->red = r;
	this->green = g;
	this->blue = b;
}
