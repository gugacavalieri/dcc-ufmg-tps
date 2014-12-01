/*
 * Image.h
 *
 *  Created on: Nov 27, 2014
 *      Author: gustavo
 */

#ifndef SRC_IMG_IMAGE_H_
#define SRC_IMG_IMAGE_H_

#define DEFAULT_WIDTH 800
#define DEFAULT_HEIGHT 600

#include <string>
#include <stdio.h>
#include "Pixel.h"

using namespace std;

class Image {
public:

	int width;
	int height;
	string filePath;

	FILE *file;

	Image(int width, int height, string filePath);
	Image();
	virtual ~Image();

	void writePixel(Pixel p);
	void writeImage(Pixel * Pixels);

private:
	void writeHeader();

};

#endif /* SRC_IMG_IMAGE_H_ */
