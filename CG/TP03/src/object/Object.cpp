/*
 * Object.cpp
 *
 *  Created on: 30/11/2014
 *      Author: gustavo
 */

#include "Object.h"

Object::Object() {

}

Color Object::getColor() {
	return color;
}

Vect Object::getNormalAt(Vect intersection_position) {

	if(this->type == SPHERE) {
		// normal always points away from the center of a sphere
		Vect normal_Vect = intersection_position.vectAdd(center.negative()).normalize();
		return normal_Vect;
	}

	if (this->type == PLANE) {
		return normal;
	}

	return Vect(0,0,0);

}

double Object::findIntersection(Ray ray) {

	if (this->type == SPHERE) {
		return findIntersectionS(ray);
	}
	if (this->type == PLANE) {
		return findIntersectionP(ray);
	}

	return 0;
}

double Object::findIntersectionS(Ray ray) {
	Vect ray_origin = ray.getRayOrigin();
	double ray_origin_x = ray_origin.getVectX();
	double ray_origin_y = ray_origin.getVectY();
	double ray_origin_z = ray_origin.getVectZ();

	Vect ray_direction = ray.getRayDirection();
	double ray_direction_x = ray_direction.getVectX();
	double ray_direction_y = ray_direction.getVectY();
	double ray_direction_z = ray_direction.getVectZ();

	Vect sphere_center = center;
	double sphere_center_x = sphere_center.getVectX();
	double sphere_center_y = sphere_center.getVectY();
	double sphere_center_z = sphere_center.getVectZ();

	double b = (2 * (ray_origin_x - sphere_center_x) * ray_direction_x)
			+ (2 * (ray_origin_y - sphere_center_y) * ray_direction_y)
			+ (2 * (ray_origin_z - sphere_center_z) * ray_direction_z);
	double c = pow(ray_origin_x - sphere_center_x, 2)
			+ pow(ray_origin_y - sphere_center_y, 2)
			+ pow(ray_origin_z - sphere_center_z, 2) - (radius * radius);

	double discriminant = b * b - 4 * c;

	if (discriminant > 0) {
		/// the ray intersects the sphere

		// the first root
		double root_1 = ((-1 * b - sqrt(discriminant)) / 2) - 0.000001;

		if (root_1 > 0) {
			// the first root is the smallest positive root
			return root_1;
		} else {
			// the second root is the smallest positive root
			double root_2 = ((sqrt(discriminant) - b) / 2) - 0.000001;
			return root_2;
		}
	} else {
		// the ray missed the sphere
		return -1;
	}
}

double Object::findIntersectionP(Ray ray) {
	Vect ray_direction = ray.getRayDirection();

	double a = ray_direction.dotProduct(normal);

	if (a == 0) {
		// ray is parallel to the plane
		return -1;
	} else {
		double b = normal.dotProduct(
				ray.getRayOrigin().vectAdd(
						normal.vectMult(distance).negative()));
		return -1 * b / a;
	}
}
