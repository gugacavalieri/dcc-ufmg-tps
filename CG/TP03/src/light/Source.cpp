/*
 * Source.cpp
 *
 *  Created on: 30/11/2014
 *      Author: gustavo
 */

#include "Source.h"
#include "../util/Vect.h"

Source::Source() {
}

Vect Source::getLightPosition() {
	return Vect(0, 0, 0);
}

Color Source::getLightColor() {
	return Color(1, 1, 1, 0);
}
