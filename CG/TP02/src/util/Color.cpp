/*
 * Color.cpp
 *
 *  Created on: Nov 8, 2014
 *      Author: gustavo
 */

#include "Color.h"

/* default constructor */
/* receive a color code as a parameter */
Color::Color(int color) {
	changeColor(color);
}

Color::Color() {
	changeColor(WHITE);
}

Color::~Color() {
	// TODO Auto-generated destructor stub
}

/* change RGB color values */
void Color::changeColor(int color) {

	/* choose color code */
	if( color == RED ) {
		this->red = 255;
		this->green = 0;
		this->blue = 0;
	}

	if( color == GREEN ) {
		this->red = 48;
		this->green = 255;
		this->blue = 0;
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

/* get RGB values */
float Color::getRed() {
	return (float) this->red / RGB_LIMIT;
}

float Color::getGreen() {
	return (float) this->green / RGB_LIMIT;
}

float Color::getBlue() {
	return (float) this->blue / RGB_LIMIT;
}
