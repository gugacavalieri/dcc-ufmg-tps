#ifndef _Camera_H
#define _Camera_H

#include "../util/Vect.h"

class Camera {
public:

	Vect campos, camdir, camright, camdown;
	Vect normal;
	Vect look_at;
	double eye_y;

	void setUp();
	void debug();

	Camera();

	Camera(Vect pos, Vect dir, Vect right, Vect down, float eye_y);

	// method functions
	Vect getCameraPosition() {
		return campos;
	}
	Vect getCameraDirection() {
		return camdir;
	}
	Vect getCameraRight() {
		return camright;
	}
	Vect getCameraDown() {
		return camdown;
	}

};

#endif
