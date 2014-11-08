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


Boid::Boid(Vector pos, Vector speed, float size, int id) {
	this->position = pos;
	this->speed = speed;
	this->size = size;
	this->id = id;
}

Boid::~Boid() {
}

void Boid::drawBoid() {

	float oneSize = this->size;
	float twiceSize = (float) this->size * 2;

	Vector normal_face;

	// TODO: DRAW BOID
	//glColor3f(1,0,0);
//	glBegin(GL_POLYGON);
//		glNormal3f(this->position.x, this->position.y, this->position.z - 1.0f);
//		glVertex3f(this->position.x - oneSize, this->position.y - oneSize, 0.0f);
//		glVertex3f(this->position.x + oneSize, this->position.y - oneSize, 0.0f);
//		glVertex3f(this->position.x + oneSize, this->position.y + oneSize, 0.0f);
//		glVertex3f(this->position.x - oneSize, this->position.y + oneSize, 0.0f);
//		glNormal3f(this->position.x, this->position.y, this->position.z + 1.0f);
//		glVertex3f(this->position.x , this->position.y, this->position.z + twiceSize);
//	glEnd();

	  glBegin(GL_QUADS);        // Draw The Cube Using quads

	  	  //top
	  	glColor3f(1.0f,0.0f,0.0f);
	    glNormal3f(0.0f, 1.0f, 0.0f);
	    glVertex3f( this->position.x + oneSize, this->position.y + oneSize, this->position.z - oneSize);
	    glVertex3f( this->position.x - oneSize, this->position.y + oneSize, this->position.z - oneSize);
	    glVertex3f( this->position.x - oneSize, this->position.y + oneSize, this->position.z + oneSize);
	    glVertex3f( this->position.x + oneSize, this->position.y + oneSize, this->position.z + oneSize);

	    // bottom
	    glNormal3f(0.0f, -1.0f, 0.0f);
	    glVertex3f( this->position.x + oneSize, this->position.y - oneSize, this->position.z + oneSize);
	    glVertex3f( this->position.x - oneSize, this->position.y - oneSize, this->position.z + oneSize);
	    glVertex3f( this->position.x - oneSize, this->position.y - oneSize, this->position.z - oneSize);
	    glVertex3f( this->position.x + oneSize, this->position.y - oneSize, this->position.z - oneSize);

	    // front
	    glNormal3f(0.0f, 0.0f, 1.0f);
	    glVertex3f( this->position.x + oneSize, this->position.y + oneSize, this->position.z + oneSize);
	    glVertex3f( this->position.x - oneSize, this->position.y + oneSize, this->position.z + oneSize);
	    glVertex3f( this->position.x - oneSize, this->position.y - oneSize, this->position.z + oneSize);
	    glVertex3f( this->position.x + oneSize, this->position.y - oneSize, this->position.z + oneSize);

	    // back
	    glNormal3f(0.0f, 0.0f, -1.0f);
	    glVertex3f( this->position.x + oneSize, this->position.y - oneSize, this->position.z - oneSize);
	    glVertex3f( this->position.x - oneSize, this->position.y - oneSize, this->position.z - oneSize);
	    glVertex3f( this->position.x - oneSize, this->position.y + oneSize, this->position.z - oneSize);
	    glVertex3f( this->position.x + oneSize, this->position.y + oneSize, this->position.z - oneSize);

	    glNormal3f(-1.0f, 0.0f, 0.0f);
	    glVertex3f( this->position.x - oneSize, this->position.y + oneSize, this->position.z + oneSize);
	    glVertex3f( this->position.x - oneSize, this->position.y + oneSize, this->position.z - oneSize);
	    glVertex3f( this->position.x - oneSize, this->position.y - oneSize, this->position.z - oneSize);
	    glVertex3f( this->position.x - oneSize, this->position.y - oneSize, this->position.z + oneSize);

	    glNormal3f(1.0f, 0.0f, 0.0f);
	    glVertex3f( this->position.x + oneSize, this->position.y + oneSize, this->position.z - oneSize);
	    glVertex3f( this->position.x + oneSize, this->position.y + oneSize, this->position.z + oneSize);
	    glVertex3f( this->position.x + oneSize, this->position.y - oneSize, this->position.z + oneSize);
	    glVertex3f( this->position.x + oneSize, this->position.y - oneSize, this->position.z - oneSize);
	  glEnd();            // End Drawing The Cube - See more at: http://www.codemiles.com/c-opengl-examples/draw-3d-cube-using-opengl-t9018.html#sthash.1j1Un7PS.dpuf

}

void Boid::updatePosition(const Vector& v) {
	this->position = this->position + v;
}

void Boid::updateSpeed(const Vector& v) {
	this->speed = v;
}

void Boid::setSize(float size) {
	this->size = size;
}

void Boid::changeColor(int* color) {
	this->color = color;
}
