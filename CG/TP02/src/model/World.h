/*
 * World.h
 *
 */

#ifndef MODEL_WORLD_H_
#define MODEL_WORLD_H_

#define WORLD_BOUNDARIES 1000.0f
#define WORLD_HEIGHT 1000.0f

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

	float tower_base;
	float tower_height;
	int tower_slice_stack;
	float world_size;

};

#endif /* MODEL_WORLD_H_ */
