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
#define MAX_BOID_SIZE 10
#define MAX_BOID_DISTANCE 100
#define NORMALIZE_FLOCK_RULES 2
#define MIN_INITIAL_POS 100
#define LEADER_SIZE 5
#define OBJECT_MIN_DISTANCE 1750

#define MAX_INITIAL_BOIDS 20

#define LEADER_SPEED 3

#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3

#include <list>

#include "../util/vector.h"
#include "../util/Random.h"
#include "Boid.h"
#include "WorldObject.h"


using namespace std;

class Flock {
public:

	int max_distance_from_flock;
	int max_boid_size;

	Vector flock_center;
	Vector flock_speed;

	Flock(float central_tower_height, float world_size);
	virtual ~Flock();

	void update_boids(list<WorldObject> objects);
	void update_flock_variables();
	void draw_boids();

	void add_new_boid();
	void remove_boid();

	void direct_boid_leader(int direction);
	Vector get_leader_position();

	void debug_flock();

	Boid leader;

private:

	list<Boid> boids;
	int idCounter;
	Random rand;

	float y_rotation;
	float x_rotation;

	/* Rule 1: Boids try to fly towards the centre of mass of neighbouring boids */
	Vector update_cohesion(Boid b);
	/* Rule 2: Boids try to keep a small distance away from other objects (including other boids) */
	Vector update_separation(Boid b);
	/* Rule 3: Boids try to match velocity with near boids */
	Vector update_alignment(Boid b);
	/* Rule 4: Tendency towards a particular place */
	Vector tend_to_place(Boid b, Vector place);
	/* Rule 5: Avoid objects */
	Vector avoid_objects(Boid b, list<WorldObject> objects);

	int generate_new_id();
	void populate_flock();

};

#endif /* MODEL_FLOCK_H_ */
