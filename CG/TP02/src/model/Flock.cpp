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

}

Flock::~Flock() {
	// TODO Auto-generated destructor stub
}

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

//		printf("updating boid %d\n.pos: (%f,%f,%f), speed: (%f,%f,%f)\n",
//				nextBoid.id, nextBoid.position.x, nextBoid.position.y,
//				nextBoid.position.z, nextBoid.speed.x, nextBoid.speed.y,
//				nextBoid.speed.z);

		i++;
	}

	/* update flock variables */
	update_flock_variables();

}

void Flock::draw_boids() {

	/* draw leader boid */
	leader.drawBoid();

	/* draw every boid in the list!	*/
	list<Boid>::iterator i = boids.begin();
	while (i != boids.end()) {
		Boid nextBoid = *i;
		nextBoid.drawBoid();
		i++;
	}

}

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

void Flock::add_new_boid() {

	/* generate new boid position */
	Vector boid_pos(
			flock_center.x + rand.generate_random_f(0, max_distance_from_flock),
			flock_center.y + rand.generate_random_f(0, max_distance_from_flock),
			flock_center.z
					+ rand.generate_random_f(0, max_distance_from_flock));

	Vector boid_speed(rand.generate_random_f(0, MAX_BOID_SPEED), 0,
			rand.generate_random_f(0, MAX_BOID_SPEED));

	float boid_size = rand.generate_random_f(0, max_boid_size);

	Boid new_boid(boid_pos, boid_speed, LEADER_SIZE, generate_new_id(), RED);

//	printf(
//			"generating new flock\n.pos: (%f,%f,%f), speed: (%f,%f,%f), size: %f\n",
//			boid_pos.x, boid_pos.y, boid_pos.z, boid_speed.x, boid_speed.y,
//			boid_speed.z, boid_size);

	printf(
			"generating new flock\n.pos: (%f,%f,%f), speed: (%f,%f,%f), size: %f\n",
			new_boid.position.x, new_boid.position.y, new_boid.position.z,
			new_boid.speed.x, new_boid.speed.y, new_boid.speed.z,
			new_boid.size);

	boids.push_back(new_boid);

	this->idCounter++;

}

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

	printf("updating flock variables\n");
	printf(".pos: (%f,%f,%f), speed: (%f,%f,%f)\n", position.x, position.y,
			position.z, speed.x, speed.y, speed.z);

	this->flock_center = position;
	this->flock_speed = speed;

}

Vector Flock::tend_to_place(Boid b, Vector place) {

	Vector result = place;

	return (result - b.position) / 100;

}

void Flock::direct_boid_leader(int direction) {

	Vector normal_speed;

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

	normal_speed.Normalize();
	normal_speed = normal_speed / NORMALIZE_FLOCK_RULES;

	this->leader.speed = this->leader.speed + normal_speed;
}

Vector Flock::get_leader_position() {
	return this->leader.position;
}

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

		if (posDifference.Length() < OBJECT_MIN_DISTANCE + currentObject.get_size()) {
			result = b.speed.Cross(Vector(0,1,0));
		}

		i++;
	}

	return result ;

}

int Flock::generate_new_id() {
	int old_id = this->idCounter;
	this->idCounter++;
	return old_id;
}
