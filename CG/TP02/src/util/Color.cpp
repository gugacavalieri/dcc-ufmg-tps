/*
 * Color.cpp
 *
 *  Created on: Nov 8, 2014
 *      Author: gustavo
 */

#include "Color.h"

Color::Color(int color) {
	changeColor(color);
}

Color::~Color() {
	// TODO Auto-generated destructor stub
}

/* change RGB color values */
void Color::changeColor(int color) {

	/* choose color type */
	if( color == RED ) {
		this->red = 255;
		this->green = 0;
		this->blue = 0;
	}

	if( color == GREEN ) {
		this->red = 16;
		this->green = 133;
		this->blue = 47;
	}

	if( color == BLUE ) {
		this->red = 0;
		this->green = 0;
		this->blue = 255;
	}

	if( color == YELLOW ) {
		this->red = 243;
		this->green = 255;
		this->blue = 13;
	}

	if( color == WHITE ) {
		this->red = 255;
		this->green = 255;
		this->blue = 255;
	}
}

int Color::getRed() {
	return this->red;
}

int Color::getGreen() {
	return this->green;
}

int Color::getBlue() {
	return this->blue;
}

Color::Color() {
}
