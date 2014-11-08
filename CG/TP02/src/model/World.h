/*
 * World.h
 *
 */

#ifndef MODEL_WORLD_H_
#define MODEL_WORLD_H_

#define WORLD_BOUNDARIES 10000.0f
#define WORLD_HEIGHT 5000.0f

#include "../util/Color.h"

class World {
public:
	World();
	virtual ~World();
	void draw_world();

	float getTowerHeight();
	float getWorldSize();

private:
	void draw_field();
	void draw_tower();
	void draw_walls();

	Color fieldColor;

	float tower_base;
	float tower_height;
	int tower_slice_stack;
	float world_size;

};

#endif /* MODEL_WORLD_H_ */
