/*
 * Vect.cpp
 *
 *  Created on: 30/11/2014
 *      Author: gustavo
 */

#include "Vect.h"

Vect::Vect(double x, double y, double z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Vect::Vect() {
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

double Vect::magnitude() {
	return sqrt((x * x) + (y * y) + (z * z));
}

Vect Vect::normalize() {
	double magnitude = sqrt((x * x) + (y * y) + (z * z));
	return Vect(x / magnitude, y / magnitude, z / magnitude);
}

Vect Vect::negative() {
	return Vect (-x, -y, -z);
}

double Vect::dotProduct(Vect v) {
	return x*v.getVectX() + y*v.getVectY() + z*v.getVectZ();
}

Vect Vect::crossProduct(Vect v) {
	return Vect (y*v.getVectZ() - z*v.getVectY(), z*v.getVectX() - x*v.getVectZ(), x*v.getVectY() - y*v.getVectX());
}

Vect Vect::vectAdd(Vect v) {
	return Vect (x + v.getVectX(), y + v.getVectY(), z + v.getVectZ());
}

Vect Vect::vectMult(double scalar) {
	return Vect (x*scalar, y*scalar, z*scalar);
}
