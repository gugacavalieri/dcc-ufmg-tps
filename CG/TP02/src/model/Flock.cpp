/*
 * Flock.cpp
 *
 *  Created on: Oct 25, 2014
 *      Author: gustavo
 */

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "Flock.h"

Flock::Flock(float central_tower_height, float world_size) {
	this->idCounter = 0;

	//TODO: MAX DISTANCE FROM FLOCK
	this->max_distance_from_flock = rand.generate_random_f(0,
	MAX_DISTANCE_FROM_FLOCK);

	this->max_boid_size = rand.generate_random_f(0, MAX_BOID_SIZE);

	/* initiate flock at a random point in world space */
	this->flock_center = Vector(
			rand.generate_random_f(MIN_INITIAL_POS, world_size / 2),
			rand.generate_random_f(0, central_tower_height / 2),
			rand.generate_random_f(MIN_INITIAL_POS, world_size / 2));

	this->leader = Boid(
			Vector(flock_center.x, flock_center.y, flock_center.z + 20.0f),
			Vector(0, 0, 3), LEADER_SIZE, generate_new_id(), WHITE);

	this->x_rotation = 0;
	this->y_rotation = 0;

	populate_flock();

}

Flock::~Flock() {
	// TODO Auto-generated destructor stub
}

/* update every boid to maintain flocking behavior */
void Flock::update_boids(list<WorldObject> objects) {

	/* update leader position */
	leader.position = leader.position + leader.speed;

	Vector rule1, rule2, rule3, rule4, rule5;

	list<Boid>::iterator i = boids.begin();
	while (i != boids.end()) {
		Boid &nextBoid = *i;

		/* calculate flock variables */
		if (boids.size() > 1) {
			rule1 = update_cohesion(nextBoid);
			rule2 = update_separation(nextBoid) / 100;
			rule3 = update_alignment(nextBoid);
		}

		rule4 = tend_to_place(nextBoid, leader.position);
		rule5 = avoid_objects(nextBoid, objects);

		/* update speed and position */
		nextBoid.speed = nextBoid.speed + rule1 + rule2 + rule3 + rule4 + rule5;
		nextBoid.speed = nextBoid.speed / NORMALIZE_FLOCK_RULES;
		nextBoid.position = nextBoid.position + nextBoid.speed;

		i++;
	}

	/* update flock variables */
	update_flock_variables();

}

/* draw every boid in the flock */
void Flock::draw_boids() {

	/* draw leader boid */
	leader.drawBoid();

	/* draw every boid in the list!	*/
	list<Boid>::iterator i = boids.begin();
	while (i != boids.end()) {
		Boid &nextBoid = *i;
		nextBoid.drawBoid();
		i++;
	}

}

/* floking rule */
/* Rule 1: Boids try to fly towards the centre of mass of neighbouring boids */
Vector Flock::update_cohesion(Boid b) {

	Vector result;

	list<Boid>::iterator i = boids.begin();
	while (i != boids.end()) {
		Boid nextBoid = *i;
		if (nextBoid.id != b.id) {
			result = result + nextBoid.position;
		}
		i++;
	}

	result = result / (boids.size() - 1);
	return (result - b.position) / 100;
}

/* flocking rule */
/* Rule 2: Boids try to keep a small distance away from other objects (including other boids) */
Vector Flock::update_separation(Boid b) {

	Vector result;

	list<Boid>::iterator i = boids.begin();
	while (i != boids.end()) {
		Boid nextBoid = *i;
		if (nextBoid.id != b.id) {

			Vector posDifference = nextBoid.position - b.position;

			if (posDifference.Length() < MAX_BOID_DISTANCE) {
				result = result - posDifference;
			}

		}

		i++;
	}

	return result;

}

/* add new boid to the flock*/
void Flock::add_new_boid() {

	/* generate new boid position */
	Vector boid_pos(
			flock_center.x + rand.generate_random_f(0, max_distance_from_flock),
			flock_center.y + rand.generate_random_f(0, max_distance_from_flock),
			flock_center.z
					+ rand.generate_random_f(0, max_distance_from_flock));

	/* generate boid speed */
	Vector boid_speed(rand.generate_random_f(0, MAX_BOID_SPEED), 0,
			rand.generate_random_f(0, MAX_BOID_SPEED));

	/* create boid */
	Boid new_boid(boid_pos, boid_speed, LEADER_SIZE, generate_new_id(), RED);

	/* add boid to the list **/
	boids.push_back(new_boid);

}

/* flocking rule */
/* Rule 3: Boids try to match velocity with near boids */
Vector Flock::update_alignment(Boid b) {

	Vector result;

	list<Boid>::iterator i = boids.begin();
	while (i != boids.end()) {

		Boid nextBoid = *i;

		if (nextBoid.id != b.id) {
			result = result + nextBoid.speed;
		}

		i++;
	}

	result = result / (boids.size() - 1);

	return (result - b.speed) / 8;

}

void Flock::update_flock_variables() {

	Vector position;
	Vector speed;

	/* for each boid, add its position to result vector	 */
	list<Boid>::iterator i = boids.begin();
	while (i != boids.end()) {
		Boid nextBoid = *i;
		position = position + nextBoid.position;
		speed = speed + nextBoid.speed;

		i++;
	}

	/* get average position and speed */
	position = position / boids.size();
	speed = speed / boids.size();

	this->flock_center = position;
	this->flock_speed = speed;

}

/* flocking rule */
/* boids tend to go to a particular place */
Vector Flock::tend_to_place(Boid b, Vector place) {

	Vector result = place;

	return (result - b.position) / 100;

}

/* control boid leader direction */
void Flock::direct_boid_leader(int direction) {

	Vector normal_speed;

	/* decide new direction and calculate speed vector */
	if (direction == RIGHT) {
		normal_speed = this->leader.speed.Cross(Vector(0, 1, 0));
	}

	if (direction == LEFT) {
		normal_speed = this->leader.speed.Cross(Vector(0, -1, 0));
	}

	if (direction == UP) {
		normal_speed = this->leader.speed.Cross(Vector(1, 0, 0));
	}

	if (direction == DOWN) {
		normal_speed = this->leader.speed.Cross(Vector(-1, 0, 0));
	}

	this->x_rotation = normal_speed.x - leader.speed.x;
	this->y_rotation = normal_speed.y - leader.speed.y;

	normal_speed.Normalize();
	normal_speed = normal_speed / NORMALIZE_FLOCK_RULES;

	this->leader.speed = this->leader.speed + normal_speed;
}

/* return leader position */
Vector Flock::get_leader_position() {
	return this->leader.position;
}

/* remove boid from list */
void Flock::remove_boid() {
	/* flock must have at least one boid */
	if (boids.size() > 1)
		this->boids.pop_back();
}

/* avoid world objects */
Vector Flock::avoid_objects(Boid b, list<WorldObject> objects) {

	Vector result;

	/* draw every object in world	*/
	list<WorldObject>::iterator i = objects.begin();
	while (i != objects.end()) {
		WorldObject currentObject = *i;

		Vector posDifference = currentObject.get_center_of_mass() - b.position;

		if (posDifference.Length()
				< OBJECT_MIN_DISTANCE + currentObject.get_size()) {
			result = b.speed.Cross(Vector(0, 1, 0));
		}

		i++;
	}

	return result;

}

/* generate new boid id */
int Flock::generate_new_id() {
	int old_id = this->idCounter;
	this->idCounter++;
	return old_id;
}

/* debug flock variables */
void Flock::debug_flock() {

	/* print flock values */
	printf("#### DEBUGING FLOCK ####\n");
	printf("Boids counter: %ld | flock center: (%3f,%3f,%3f)\n", boids.size(),
			flock_center.x, flock_center.y, flock_center.z);

	/* print every boid variables */
	list<Boid>::iterator i = boids.begin();
		while (i != boids.end()) {
			Boid currentBoid = *i;
			currentBoid.debug_boid();
			i++;
		}

}

void Flock::populate_flock() {

	int i;
	int num_boids = rand.generate_random_i(5, MAX_INITIAL_BOIDS);

	for(i = 0 ; i < num_boids ; i++) {
		add_new_boid();
	}

}
