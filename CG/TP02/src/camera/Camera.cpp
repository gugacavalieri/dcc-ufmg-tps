/*
 * Camera.cpp
 *
 *  Created on: Oct 25, 2014
 *      Author: gustavo
 */

#include <GL/glut.h>
#include <stdio.h>
#include "Camera.h"
#include "../util/vector.h"

Camera::Camera(const Vector &pos, const Vector &look, const Vector &normal, float central_tower_height) {
	this->position = pos;
	this->lookingAt = look;
	this->normal = normal;
	this->window_aspect = 1;
	this->central_tower_height = central_tower_height;
	this->mode = 0;
	this->camera_zoom = CAMERA_DISTANCE;
}

Camera::~Camera() {
	// TODO Auto-generated destructor stub
}

void Camera::update_position(const Vector& v) {
	this->position = this->position + v;
}

void Camera::update_lookingAt(const Vector& v) {
	this->lookingAt = v;
}

void Camera::update_normal(const Vector& v) {
	this->normal = v;
}

void Camera::set_window_aspect(float window_aspect) {
	this->window_aspect = window_aspect;
}

void Camera::update_camera(Vector& target, Vector speed) {

	this->lookingAt = target;

	/* behind flock viewing mode */
	if(mode == 0) {
		this->position = target - multiply(speed, camera_zoom);
	}

	/* flock side viewing mode */
	if(mode == 1) {

		camera_zoom = MAX_ZOOM;

		/* normal vector to flock speed vector */
		Vector normal_speed;
		normal_speed = speed.Cross(Vector(0,1,0));
		this->position = target - multiply(normal_speed, camera_zoom);
	}

	/* tower top viewing mode */
	if(mode == 2) {
		this->position = Vector(0, central_tower_height, 0);
	}

	printf("updating camera: pos: (%f,%f,%f) , lookingAt: (%f,%f,%f)\n",
			this->position.x, this->position.y, this->position.z,
			this->lookingAt.x, this->lookingAt.y, this->lookingAt.z);

}

void Camera::look_at() {

	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();
	// Especifica posição do observador e do alvo
	gluLookAt(position.x, position.y, position.z, lookingAt.x, lookingAt.y,
			lookingAt.z, normal.x, normal.y, normal.z);

}

/* change camera viewing mode */
void Camera::change_mode() {
	this->mode = (this->mode +1) % CAMERA_MODES;
}

void Camera::zoom(int mode) {

	/* zoom in or zoom out ? */
	if( mode == ZOOM_IN ) {
		if(this->camera_zoom > MIN_ZOOM)
			this->camera_zoom -= 10;
	}

	else{
		if(this->camera_zoom < MAX_ZOOM)
			this->camera_zoom += 10;
	}

}
