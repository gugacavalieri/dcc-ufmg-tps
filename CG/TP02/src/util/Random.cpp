/*
 * Random.cpp
 *
 */

#include "Random.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

Random::Random() {
	/* random numbers seed */
	srand(time(NULL));
}

Random::~Random() {
	// TODO Auto-generated destructor stub
}

float Random::generate_random_f(int lb, int hb) {

	/* check if lower bound and higher bound are equal */
	if( lb == hb )
		return lb;

	float random_number = lb + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(hb-lb)));

	return random_number;

}

int Random::generate_random_i(int lb, int hb) {

	if( lb == hb )
		return lb;

	int random_number = lb + rand() % (hb-lb);

	return random_number;
}
