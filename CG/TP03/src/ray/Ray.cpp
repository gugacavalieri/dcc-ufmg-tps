/*
 * Ray.cpp
 *
 *  Created on: 30/11/2014
 *      Author: gustavo
 */

#include "Ray.h"

Ray::Ray () {
	origin = Vect(0,0,0);
	direction = Vect(1,0,0);
}

Ray::Ray (Vect o, Vect d) {
	origin = o;
	direction = d;
}


