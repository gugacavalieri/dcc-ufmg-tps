/*
 * WorldObject.cpp
 *
 *  Created on: Nov 8, 2014
 *      Author: gustavo
 */

#include "WorldObject.h"
#include "../util/vector.h"
#include <GL/glut.h>
#include <stdio.h>

WorldObject::WorldObject() {
	this->type = SPHERE;
	this->size = DEFAULT_SIZE;
	this->stacks = DEFAULT_STACKS;
}

WorldObject::WorldObject(Vector position, int type, int size, int stacks,
		int color) {

	this->type = type;
	this->position = position;
	this->size = size;
	this->stacks = stacks;

	this->color.changeColor(color);

	calculate_center_of_mass();

}

WorldObject::~WorldObject() {
	// TODO Auto-generated destructor stub
}

void WorldObject::draw_object() {

	glPushMatrix();

	/* translate object to its position */
	glTranslatef(position.x, position.y, position.z);

	/* paint object ! */
	glColor3f(color.getRed(), color.getGreen(), color.getBlue());

	/* select object type */
	if (type == SPHERE) {
		glutSolidSphere(size, stacks, stacks);
	}

	if (type == CONE) {
		/* rotate cone */
		glRotatef(-90, 1, 0, 0);
		glutSolidCone(size, size + 500, stacks, stacks);
	}

	/* end transformation */
	glPopMatrix();

}

Vector WorldObject::get_center_of_mass() {
	return this->center_of_mass;
}

Vector WorldObject::get_position() {
	return this->position;
}

int WorldObject::get_type() {
	return this->type;
}

void WorldObject::change_color(int color) {
	this->color.changeColor(color);
}

int WorldObject::get_size() {
	return this->size;
}

void WorldObject::debug_object() {

	if (type == SPHERE) {
		printf("Object: SPHERE | Center of Mass:(%3f,%3f,%3f) | Size: %3f\n",
				center_of_mass.x, center_of_mass.y, center_of_mass.z, size);
	}

	if (type == CONE) {
			printf("Object: CONE | Center of Mass:(%3f,%3f,%3f) | Size: %3f\n",
					center_of_mass.x, center_of_mass.y, center_of_mass.z, size);
		}

}

void WorldObject::calculate_center_of_mass() {

	/* check object type */
	if (this->type == CONE) {
		this->center_of_mass = Vector(this->position.x, size / 2,
				this->position.z);
	}

	else
		this->center_of_mass = position;

}
