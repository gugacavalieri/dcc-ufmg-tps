/*
 * Image.cpp
 *
 *  Created on: Nov 27, 2014
 *      Author: gustavo
 */

#include "Image.h"

Image::Image() {
	this->file = NULL;
	this->width = DEFAULT_WIDTH;
	this->height = DEFAULT_HEIGHT;
}

Image::Image(int width, int height, string filePath) {

	this->width = width;
	this->height = height;
	this->filePath = filePath;

	this->file = fopen(filePath.c_str(), "w");

	writeHeader();

}

Image::~Image() {
	fclose(this->file);
}

void Image::writePixel(Pixel p) {
	fprintf(this->file, "%d %d %d\n", p.R, p.G, p.B);
}

/* write whole image to file */
void Image::writeImage(Pixel* Pixels) {

	int size = this->width*this->height;

	for(int i=size-1; i >=0 ; i --) {
		writePixel(Pixels[i]);
	}

}

/* write image header to file */
void Image::writeHeader() {

	fprintf(this->file, "P3\n");
	fprintf(this->file, "%d %d\n", this->width, this->height);
	fprintf(this->file, "255\n");

}
