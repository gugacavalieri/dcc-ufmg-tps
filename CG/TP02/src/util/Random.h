/*
 * Random.h
 *
 define a random number generator
 */

#ifndef UTIL_RANDOM_H_
#define UTIL_RANDOM_H_

class Random {
public:
	Random();
	virtual ~Random();

	/* generate integer and float numbers */
	float generate_random_f(int lb, int hb);
	int generate_random_i(int lb, int hb);
};

#endif /* UTIL_RANDOM_H_ */
