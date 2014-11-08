/*
 * Flock.h
 *
 * This class model a flock.
 * A flock contains 'n' boids
 *
 *  Created on: Oct 25, 2014
 *      Author: gustavo
 */

#ifndef MODEL_FLOCK_H_
#define MODEL_FLOCK_H_

#define MAX_DISTANCE_FROM_FLOCK 100
#define MAX_BOID_SPEED 1
#define MAX_BOID_SIZE 20
#define BOIDS_DISTANCE 10.0f
#define NORMALIZE_FLOCK_RULES 2
#define MIN_INITIAL_POS 100

#include <list>

#include "../util/vector.h"
#include "../util/Random.h"
#include "Boid.h"


using namespace std;

class Flock {
public:

	int max_distance_from_flock;
	int max_boid_size;

	Vector flock_center;
	Vector flock_speed;

	Flock(float central_tower_height, float world_size);
	virtual ~Flock();

	void update_boids();
	void update_flock_variables();
	void draw_boids();

	void add_new_boid();

private:

	list<Boid> boids;
	int idCounter;
	Random rand;

	/* Rule 1: Boids try to fly towards the centre of mass of neighbouring boids */
	Vector update_cohesion(Boid b);
	/* Rule 2: Boids try to keep a small distance away from other objects (including other boids) */
	Vector update_separation(Boid b);
	/* Rule 3: Boids try to match velocity with near boids */
	Vector update_alignment(Boid b);

};

#endif /* MODEL_FLOCK_H_ */