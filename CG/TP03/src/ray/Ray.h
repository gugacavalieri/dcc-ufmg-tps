#ifndef _RAY_H
#define _RAY_H

#include "../util/Vect.h"

class Ray {
	Vect origin, direction;
	
	public:
	
	Ray ();
	
	Ray (Vect, Vect);
	
	// method functions
	Vect getRayOrigin () { return origin; }
	Vect getRayDirection () { return direction; }
	
};

#endif
