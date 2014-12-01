#ifndef _VECT_H
#define _VECT_H

#include "math.h"

class Vect {
	
	public:
	
	double x, y, z;

	Vect ();
	
	Vect (double x, double y, double z);
	
	// method functions
	double getVectX() { return x; }
	double getVectY() { return y; }
	double getVectZ() { return z; }
	
	double magnitude ();
	
	Vect normalize ();
	
	Vect negative ();
	
	double dotProduct(Vect v);
	
	Vect crossProduct(Vect v);
	
	Vect vectAdd (Vect v);

	Vect vectMult (double scalar);
};



#endif
