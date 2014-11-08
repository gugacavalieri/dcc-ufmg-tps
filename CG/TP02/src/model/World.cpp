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
	this->number_of_objects = rand.generate_random_i(MIN_NUMBER_OBJECTS, MAX_NUMBER_OBJECTS);


	/* generate world objects */
	generate_objects();
}

World::~World() {
	// TODO Auto-generated destructor stub
}

void World::draw_world() {

	draw_tower();
	draw_field();
	draw_walls();
	draw_objects();

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
	glColor3f(0.4, 0.4, 0.4);

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

void World::add_new_object(int type) {

	float objectSize = rand.generate_random_f(MIN_OBJECT_SIZE, MAX_OBJECT_SIZE);
	Vector position;

	/* check object type */
	/* cones must be on the ground */
	if (type == CONE) {
		position = Vector(rand.generate_random_f(-world_size, world_size), 0,
				rand.generate_random_f(-world_size, world_size));
	}

	else {
		position = Vector(rand.generate_random_f(-world_size, world_size),
				rand.generate_random_f(objectSize, tower_height),
				rand.generate_random_f(-world_size, world_size));
	}

	WorldObject new_object(position, type, objectSize, 30, WHITE);

	objects.push_back(new_object);

}

void World::remove_object() {

	if( objects.size() > 1 )
		objects.pop_back();

}

void World::draw_walls() {

	glColor3f(0.0f, 0.5f, 1.0f);

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

void World::draw_objects() {

	/* draw every object in the list!	*/
	list<WorldObject>::iterator i = objects.begin();
	while (i != objects.end()) {
		WorldObject currentObject = *i;
		currentObject.draw_object();
		i++;
	}

}

list<WorldObject> World::get_objects() {
	return this->objects;
}

void World::generate_objects() {

	int i;

	for(i = 0 ; i < number_of_objects ; i ++) {
		add_new_object(rand.generate_random_i(0, OBJECT_TYPES));
	}

}
