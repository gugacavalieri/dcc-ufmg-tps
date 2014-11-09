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

/* rotation axis */
#define X_AXIS 0
#define Y_AXIS 1
#define Z_AXIS 2

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
	void debug_boid();

private:

	float wing_animation;
	bool wing_up;

	float rotation;
	int rotation_axis;

	void draw_body();
	void draw_wings();

};

#endif /* MODEL_BOID_H_ */
