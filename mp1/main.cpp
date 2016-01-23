#include <iostream>

#include "rgbapixel.h"
#include "png.h"

using namespace std;

/**
*rotate the image by 180 degrees
*/
PNG rotateImage(PNG original) {
	PNG result (original.width(), original.height());
	for (size_t i=0; i<original.width(); i++) {
		for (size_t j=0; j<original.height(); j++) {
			result(i,j)->red = original(original.width()-1-i,
				original.height()-1-j)->red;
			result(i,j)->green = original(original.width()-1-i,
				original.height()-1-j)->green;
			result(i,j)->blue = original(original.width()-1-i,
				original.height()-1-j)->blue;
		}
	}
	return result;
}

int main() {
	PNG image ("in.png"); // open a bitmap image named in.png
	image = rotateImage(image); // rotate the image by 180 degrees
	image.writeToFile("out.png"); // write image to the file out.png
	return 0;
}


