/*
 * WorldObject.h
 *
 *  Created on: Nov 8, 2014
 *      Author: gustavo
 */

#ifndef MODEL_WORLDOBJECT_H_
#define MODEL_WORLDOBJECT_H_

#define SPHERE 0
#define CONE 1
#define DEFAULT_SIZE 5
#define DEFAULT_STACKS 20

#define OBJECT_TYPES 2

#include "../util/vector.h"
#include "../util/Color.h"

class WorldObject {
public:

	WorldObject();
	WorldObject(Vector position, int type, int size, int stacks, int color);
	virtual ~WorldObject();

	void draw_object();

	/* getter and setters*/
	Vector get_center_of_mass();
	Vector get_position();
	int get_type();
	int get_size();
	void change_color(int color);

	void debug_object();

private:

	Vector center_of_mass;
	Vector position;
	int type;
	int size;
	int stacks;
	Color color;

	void calculate_center_of_mass();
};

#endif /* MODEL_WORLDOBJECT_H_ */
