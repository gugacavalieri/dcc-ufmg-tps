/*
 * Camera.h
 *
 *  Created on: Oct 25, 2014
 *      Author: gustavo
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#define CAMERA_MODES 3
#define CAMERA_DISTANCE 80

#include "../util/vector.h"

class Camera {
public:

	Camera(const Vector &pos, const Vector &look, const Vector &normal, float central_tower_height);
	virtual ~Camera();

	void update_position(const Vector &v);
	void update_lookingAt(const Vector &v);
	void update_normal(const Vector &v);
	void update_camera(Vector &target);
	void look_at();
	void set_window_aspect(float window_aspect);
	void change_mode();

private:
	Vector position;
	Vector lookingAt;
	Vector normal;
	float window_aspect;
	float central_tower_height;
	int mode;

};

#endif /* CAMERA_H_ */