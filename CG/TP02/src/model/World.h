/*
 * World.h
 *
 */

#ifndef MODEL_WORLD_H_
#define MODEL_WORLD_H_

#define WORLD_BOUNDARIES 10000.0f
#define WORLD_HEIGHT 5000.0f

#define MAX_OBJECT_SIZE 900
#define MIN_OBJECT_SIZE 50

#define MAX_NUMBER_OBJECTS 20
#define MIN_NUMBER_OBJECTS 5

#include "../util/Color.h"
#include "../util/Random.h"
#include "WorldObject.h"
#include <list>

using namespace std;

class World {
public:
	World();
	virtual ~World();
	void draw_world();

	float getTowerHeight();
	float getWorldSize();

	void add_new_object(int type);
	void remove_object();
	list<WorldObject> get_objects();

private:

	void draw_field();
	void draw_tower();
	void draw_walls();
	void draw_objects();

	void generate_objects();

	Random rand;

	list<WorldObject> objects;
	int number_of_objects;

	Color fieldColor;

	float tower_base;
	float tower_height;
	int tower_slice_stack;
	float world_size;

};

#endif /* MODEL_WORLD_H_ */
