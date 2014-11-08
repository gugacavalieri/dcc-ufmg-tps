/*
 * World.cpp
 *
 */

#include "World.h"

#include <GL/glut.h>

World::World() {
	this->tower_base = 200.0f;
	this->tower_height = WORLD_HEIGHT;
	this->tower_slice_stack = 20;
	this->world_size = WORLD_BOUNDARIES;
	fieldColor.changeColor(GREEN);
}

World::~World() {
	// TODO Auto-generated destructor stub
}

void World::draw_world() {

	draw_field();
	draw_tower();
	draw_walls();

}

void World::draw_field() {

	glBegin(GL_QUADS);
	glColor3f(fieldColor.getRed(), fieldColor.getGreen(), fieldColor.getBlue());
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-world_size, 0.0f, -world_size);
	glVertex3f(world_size, 0.0f, -world_size);
	glVertex3f(world_size, 0.0f, world_size);
	glVertex3f(-world_size, 0.0f, world_size);
	glEnd();

}

void World::draw_tower() {

	/* choose tower color */
	glColor3f(255, 255, 255);

	/* rotates cone 90 degrees around 'x'*/
	/* draw glut solid cone! */
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	glutSolidCone(tower_base, tower_height, tower_slice_stack,
			tower_slice_stack);
	glPopMatrix();
}

float World::getTowerHeight() {
	return this->tower_height;
}

float World::getWorldSize() {
	return this->world_size;
}

void World::draw_walls() {

	glColor3f(0.0f, 0.0f, 1.0f);

	glBegin(GL_QUADS);

	// front
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(world_size, tower_height, world_size);
	glVertex3f(-world_size, tower_height, world_size);
	glVertex3f(-world_size, -tower_height, world_size);
	glVertex3f(world_size, -tower_height, world_size);

	//right
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(world_size, tower_height, world_size);
	glVertex3f(world_size, tower_height, -world_size);
	glVertex3f(world_size, -tower_height, -world_size);
	glVertex3f(world_size, -tower_height, world_size);

	//back
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(world_size, tower_height, -world_size);
	glVertex3f(-world_size, tower_height, -world_size);
	glVertex3f(-world_size, -tower_height, -world_size);
	glVertex3f(world_size, -tower_height, -world_size);

	//left
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-world_size, tower_height, world_size);
	glVertex3f(-world_size, tower_height, -world_size);
	glVertex3f(-world_size, -tower_height, -world_size);
	glVertex3f(-world_size, -tower_height, world_size);

	glEnd();

}
