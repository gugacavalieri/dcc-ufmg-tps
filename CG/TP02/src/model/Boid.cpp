/*
 * Boid.cpp
 *
 *  Created on: Oct 20, 2014
 *      Author: gustavo
 */

#include <GL/glut.h>
#include <stdio.h>
#include "Boid.h"

#include "../util/vector.h"

/* boid constructor */
Boid::Boid(Vector pos, Vector speed, float size, int id, int color) {
	this->position = pos;
	this->speed = speed;
	this->size = size;
	this->id = id;
	this->boid_color.changeColor(color);
	this->wing_animation = 0;
	this->wing_up = true;

}

Boid::Boid() {
}

Boid::~Boid() {
}

void Boid::drawBoid() {

	draw_body();
	draw_wings();
	
}

/* update boid position */
void Boid::updatePosition(const Vector& v) {
	this->position = this->position + v;
}

/* update boid vector speed */
void Boid::updateSpeed(const Vector& v) {
	this->speed = v;
}

/* change boid size */
void Boid::setSize(float size) {
	this->size = size;
}

/* change boid color */
void Boid::changeColor(int color) {
	this->boid_color.changeColor(color);
}

/* draw boid body */
void Boid::draw_body() {

	float oneSize = this->size;

	glBegin(GL_QUADS);        // Draw The Cube Using quads

	//top
	glColor3f(boid_color.getRed(), boid_color.getGreen(), boid_color.getBlue());
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(this->position.x + oneSize, this->position.y + oneSize,
			this->position.z - oneSize);
	glVertex3f(this->position.x - oneSize, this->position.y + oneSize,
			this->position.z - oneSize);
	glVertex3f(this->position.x - oneSize, this->position.y + oneSize,
			this->position.z + oneSize);
	glVertex3f(this->position.x + oneSize, this->position.y + oneSize,
			this->position.z + oneSize);

	// bottom
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(this->position.x + oneSize, this->position.y - oneSize,
			this->position.z + oneSize);
	glVertex3f(this->position.x - oneSize, this->position.y - oneSize,
			this->position.z + oneSize);
	glVertex3f(this->position.x - oneSize, this->position.y - oneSize,
			this->position.z - oneSize);
	glVertex3f(this->position.x + oneSize, this->position.y - oneSize,
			this->position.z - oneSize);

	// front
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(this->position.x + oneSize, this->position.y + oneSize,
			this->position.z + oneSize);
	glVertex3f(this->position.x - oneSize, this->position.y + oneSize,
			this->position.z + oneSize);
	glVertex3f(this->position.x - oneSize, this->position.y - oneSize,
			this->position.z + oneSize);
	glVertex3f(this->position.x + oneSize, this->position.y - oneSize,
			this->position.z + oneSize);

	// back
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(this->position.x + oneSize, this->position.y - oneSize,
			this->position.z - oneSize);
	glVertex3f(this->position.x - oneSize, this->position.y - oneSize,
			this->position.z - oneSize);
	glVertex3f(this->position.x - oneSize, this->position.y + oneSize,
			this->position.z - oneSize);
	glVertex3f(this->position.x + oneSize, this->position.y + oneSize,
			this->position.z - oneSize);

	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(this->position.x - oneSize, this->position.y + oneSize,
			this->position.z + oneSize);
	glVertex3f(this->position.x - oneSize, this->position.y + oneSize,
			this->position.z - oneSize);
	glVertex3f(this->position.x - oneSize, this->position.y - oneSize,
			this->position.z - oneSize);
	glVertex3f(this->position.x - oneSize, this->position.y - oneSize,
			this->position.z + oneSize);

	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(this->position.x + oneSize, this->position.y + oneSize,
			this->position.z - oneSize);
	glVertex3f(this->position.x + oneSize, this->position.y + oneSize,
			this->position.z + oneSize);
	glVertex3f(this->position.x + oneSize, this->position.y - oneSize,
			this->position.z + oneSize);
	glVertex3f(this->position.x + oneSize, this->position.y - oneSize,
			this->position.z - oneSize);
	glEnd();
}

/* draw boid wings */
void Boid::draw_wings() {

	float oneSize = this->size;
	float wing_size = this->size / 5;
	float wing_height = this->size / 7;

	Vector leftWall(this->position.x + oneSize, this->position.y,
			this->position.z);

	/* left wing */
	glBegin(GL_POLYGON);

	glNormal3f(0, -1, 0);
	glVertex3f(leftWall.x, leftWall.y + wing_height, leftWall.z - wing_size);
	glVertex3f(leftWall.x, leftWall.y + wing_height, leftWall.z + wing_size);
	glVertex3f(leftWall.x, leftWall.y - wing_height, leftWall.z + wing_size);
	glVertex3f(leftWall.x, leftWall.y - wing_height, leftWall.z - wing_size);

	glVertex3f(leftWall.x + oneSize,
			leftWall.y + wing_height + this->wing_animation,
			leftWall.z - wing_size);
	glVertex3f(leftWall.x + oneSize,
			leftWall.y + wing_height + this->wing_animation,
			leftWall.z + wing_size);
	glVertex3f(leftWall.x + oneSize,
			leftWall.y - wing_height + this->wing_animation,
			leftWall.z + wing_size);
	glVertex3f(leftWall.x + oneSize,
			leftWall.y - wing_height + this->wing_animation,
			leftWall.z - wing_size);

	glEnd();

	Vector rightWall(this->position.x - oneSize, this->position.y,
			this->position.z);

	/* right wing */
	glBegin(GL_POLYGON);

	glNormal3f(0, -1, 0);
	glVertex3f(rightWall.x, leftWall.y + wing_height, leftWall.z - wing_size);
	glVertex3f(rightWall.x, leftWall.y + wing_height, leftWall.z + wing_size);
	glVertex3f(rightWall.x, leftWall.y - wing_height, leftWall.z + wing_size);
	glVertex3f(rightWall.x, leftWall.y - wing_height, leftWall.z - wing_size);

	glVertex3f(rightWall.x - oneSize,
			leftWall.y + wing_height + this->wing_animation,
			leftWall.z - wing_size);
	glVertex3f(rightWall.x - oneSize,
			leftWall.y + wing_height + this->wing_animation,
			leftWall.z + wing_size);
	glVertex3f(rightWall.x - oneSize,
			leftWall.y - wing_height + this->wing_animation,
			leftWall.z + wing_size);
	glVertex3f(rightWall.x - oneSize,
			leftWall.y - wing_height + this->wing_animation,
			leftWall.z - wing_size);

	glEnd();

	if (this->wing_animation < oneSize && this->wing_up) {
		this->wing_animation += 0.1f;
	} else {
		this->wing_up = false;

		if (this->wing_animation > -oneSize && !this->wing_up) {
			this->wing_animation -= 0.1f;
		} else {
			this->wing_up = true;
		}
	}

}

/* debug boid variables */
void Boid::debug_boid() {
	printf("Boid #%d | pos:(%3f,%3f,%3f) | speed:(%3f,%3f,%3f) | size: %3f\n",
			id, position.x, position.y, position.z, speed.x, speed.y, speed.z,
			size);
}
