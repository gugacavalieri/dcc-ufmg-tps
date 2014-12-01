/*
 * Camera.cpp
 *
 *  Created on: 30/11/2014
 *      Author: gustavo
 */

#include "Camera.h"
#include <stdio.h>

Camera::Camera() {
	campos = Vect(0, 0, 0);
	camdir = Vect(0, 0, 1);
	camright = Vect(0, 0, 0);
	camdown = Vect(0, 0, 0);
	this->eye_y = 1;
}

/* debug camera variables */
void Camera::debug() {

	printf("### DEBUGGING CAMERA\n");
	printf(
			"Position: (%f,%f,%f) | Direction: (%f,%f,%f) | Right: (%f,%f,%f) | Down: (%f,%f,%f) | Y_Eye: %f\n",
			this->campos.x, this->campos.y, this->campos.z, this->camdir.x,
			this->camdir.y, this->camdir.z, this->camright.x, this->camright.y,
			this->camright.z, this->camdown.x, this->camdown.y, this->camdown.z,
			this->eye_y);

}

Camera::Camera(Vect pos, Vect dir, Vect right, Vect down, float eye_y) {
	campos = pos;
	camdir = dir;
	camright = right;
	camdown = down;
	this->eye_y = eye_y;
}

/* set up other camera vectors */
void Camera::setUp() {

	Vect Y_unit(0, 1, 0);

	Vect diff_btw(campos.getVectX() - look_at.getVectX(),
			campos.getVectY() - look_at.getVectY(),
			campos.getVectZ() - look_at.getVectZ());

	this->camdir = diff_btw.negative().normalize();
	this->camright = Y_unit.crossProduct(this->camdir).normalize();
	this->camdown = this->camright.crossProduct(this->camdir);

}
