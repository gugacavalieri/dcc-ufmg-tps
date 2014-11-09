/*
 * Boid.h
 *
 *  Created on: Oct 20, 2014
 *      Author: gustavo
 */

#ifndef MODEL_BOID_H_
#define MODEL_BOID_H_

#include "../util/vector.h"
#include "../util/Color.h"

class Boid {
public:

	Vector position;
	Vector speed;
	Color boid_color;
	float size;
	int id;

	/* contructor and destructor */
	Boid();
	Boid(Vector pos, Vector speed, float size, int id, int color);
	virtual ~Boid();

	/* boid functions */
	void drawBoid();
	void updatePosition(const Vector &v);
	void updateSpeed(const Vector &v);
	void setSize(float size);
	void changeColor(int color);

private:

	float wing_animation;
	bool wing_up;

	void draw_body();
	void draw_wings();

};

#endif /* MODEL_BOID_H_ */
