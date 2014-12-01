#ifndef _OBJECT_H
#define _OBJECT_H

#define SPHERE 1
#define PLANE 2

#include "../ray/Ray.h"
#include "../util/Vect.h"
#include "../color/Color.h"

class Object {
public:

	int type;
	double radius;
	Vect normal;
	double distance;
	Vect center;
	Color color;

	Object();

	// method functions
	Color getColor();

	Vect getNormalAt(Vect intersection_position);

	double findIntersection(Ray ray);

private:
	
	double findIntersectionS(Ray ray);
	double findIntersectionP(Ray ray);

};

#endif
