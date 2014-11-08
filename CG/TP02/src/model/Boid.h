/*
 * Boid.h
 *
 *  Created on: Oct 20, 2014
 *      Author: gustavo
 */

#ifndef MODEL_BOID_H_
#define MODEL_BOID_H_

#include "../util/vector.h"

class Boid {
public:

	Vector position;
	Vector speed;
	float size;
	int *color;
	int id;

	/* contructor and destructor */
	Boid(Vector pos, Vector speed, float size, int id);
	virtual ~Boid();

	/* boid functions */
	void drawBoid();
	void updatePosition(const Vector &v);
	void updateSpeed(const Vector &v);
	void setSize(float size);
	void changeColor(int *color);

};

#endif /* MODEL_BOID_H_ */
