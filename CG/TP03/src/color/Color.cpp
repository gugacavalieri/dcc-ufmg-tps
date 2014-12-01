/*
 * Color.cpp
 *
 *  Created on: 30/11/2014
 *      Author: gustavo
 */

#include "Color.h"

Color::Color () {
	red = 0.5;
	green = 0.5;
	blue = 0.5;
	this->special = 0;
}

Color::Color (double r, double g, double b, double s) {
	red = r;
	green = g;
	blue = b;
	special = s;
}

double Color::getColorRed() {
	return red;
}

double Color::getColorGreen() {
	return green;
}

double Color::getColorBlue() {
	return blue;
}

double Color::getColorSpecial() {
	return special;
}

void Color::setColorRed(double redValue) {
	this->red = redValue;
}

void Color::setColorGreen(double greenValue) {
	green = greenValue;
}

void Color::setColorBlue(double blueValue) {
	blue = blueValue;
}

void Color::setColorSpecial(double specialValue) {
	special = specialValue;
}

double Color::brightness() {
	return(red + green + blue)/3;
}

Color Color::colorScalar(double scalar) {
	return Color (red*scalar, green*scalar, blue*scalar, special);
}

Color Color::colorAdd(Color color) {
	return Color (red + color.getColorRed(), green + color.getColorGreen(), blue + color.getColorBlue(), special);
}

Color Color::colorMultiply(Color color) {
	return Color (red*color.getColorRed(), green*color.getColorGreen(), blue*color.getColorBlue(), special);
}

Color Color::colorAverage(Color color) {
	return Color ((red + color.getColorRed())/2, (green + color.getColorGreen())/2, (blue + color.getColorBlue())/2, special);
}

Color Color::clip() {
	double alllight = red + green + blue;
	double excesslight = alllight - 3;
	if (excesslight > 0) {
		red = red + excesslight*(red/alllight);
		green = green + excesslight*(green/alllight);
		blue = blue + excesslight*(blue/alllight);
	}
	if (red > 1) {red = 1;}
	if (green > 1) {green = 1;}
	if (blue > 1) {blue = 1;}
	if (red < 0) {red = 0;}
	if (green < 0) {green = 0;}
	if (blue < 0) {blue = 0;}

	return Color (red, green, blue, special);
}
