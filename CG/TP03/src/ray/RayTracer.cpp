/*
 * RayTracer.cpp
 *
 *  Created on: Nov 27, 2014
 *      Author: gustavo
 */

#include <vector>
#include <cmath>
#include <limits>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "RayTracer.h"
#include "Ray.h"
#include "../util/Vect.h"
#include "../img/Pixel.h"
#include "../camera/Camera.h"
#include "../color/Color.h"
#include "../light/Source.h"
#include "../light/Light.h"
#include "../object/Object.h"

RayTracer::RayTracer() {

}

void RayTracer::start() {

	int imageSize = image.width * image.height;
	Pixel *pixels = new Pixel[imageSize];

	int aadepth = 1;
	double aspectratio = (double) image.width / (double) image.height;
	double ambientlight = AMBIENT_LIGHT;
	double accuracy = MIN_ACCURACY;

	int thisone, aa_index;
	double xamnt, yamnt;

	/* for every pixel in image */
	for (int x = 0; x < image.width; x++) {
		for (int y = 0; y < image.height; y++) {

			thisone = y * image.width + x;

			// start with a blank pixel
			double tempRed[aadepth * aadepth];
			double tempGreen[aadepth * aadepth];
			double tempBlue[aadepth * aadepth];

			for (int aax = 0; aax < aadepth; aax++) {
				for (int aay = 0; aay < aadepth; aay++) {

					aa_index = aay * aadepth + aax;

					srand(time(0));

					// create the ray from the camera to this pixel
					if (aadepth == 1) {

						// start with no anti-aliasing
						if (image.width > image.height) {
							// the image is wider than it is tall
							xamnt = ((x + 0.5) / image.width) * aspectratio
									- (((image.width - image.height)
											/ (double) image.height) / 2);
							yamnt = ((image.height - y) + 0.5) / image.height;
						} else if (image.height > image.width) {
							// the imager is taller than it is wide
							xamnt = (x + 0.5) / image.width;
							yamnt = (((image.height - y) + 0.5) / image.height)
									/ aspectratio
									- (((image.height - image.width)
											/ (double) image.width) / 2);
						} else {
							// the image is square
							xamnt = (x + 0.5) / image.width;
							yamnt = ((image.height - y) + 0.5) / image.height;
						}
					} else {
						// anti-aliasing
						if (image.width > image.height) {
							// the image is wider than it is tall
							xamnt = ((x + (double) aax / ((double) aadepth - 1))
									/ image.width) * aspectratio
									- (((image.width - image.height)
											/ (double) image.height) / 2);
							yamnt = ((image.height - y)
									+ (double) aax / ((double) aadepth - 1))
									/ image.height;
						} else if (image.height > image.width) {
							// the imager is taller than it is wide
							xamnt = (x + (double) aax / ((double) aadepth - 1))
									/ image.width;
							yamnt = (((image.height - y)
									+ (double) aax / ((double) aadepth - 1))
									/ image.height) / aspectratio
									- (((image.height - image.width)
											/ (double) image.width) / 2);
						} else {
							// the image is square
							xamnt = (x + (double) aax / ((double) aadepth - 1))
									/ image.width;
							yamnt = ((image.height - y)
									+ (double) aax / ((double) aadepth - 1))
									/ image.height;
						}
					}

					Vect cam_ray_origin = this->camera.getCameraPosition();
					Vect cam_ray_direction =
							this->camera.camdir.vectAdd(
									this->camera.camright.vectMult(xamnt - 0.5).vectAdd(
											this->camera.camdown.vectMult(
													yamnt - 0.5))).normalize();

					Ray cam_ray(cam_ray_origin, cam_ray_direction);

					vector<double> intersections;

					for (size_t index = 0; index < scene_objects.size(); index++) {
						intersections.push_back(
								scene_objects.at(index).findIntersection(
										cam_ray));
					}

					int index_of_winning_object = winningObjectIndex(
							intersections);

					if (index_of_winning_object == -1) {
						// set the backgroung black
						tempRed[aa_index] = 0;
						tempGreen[aa_index] = 0;
						tempBlue[aa_index] = 0;
					} else {
						// index coresponds to an object in our scene
						if (intersections.at(index_of_winning_object)
								> accuracy) {
							// determine the position and direction vectors at the point of intersection

							Vect intersection_position = cam_ray_origin.vectAdd(
									cam_ray_direction.vectMult(
											intersections.at(
													index_of_winning_object)));
							Vect intersecting_ray_direction = cam_ray_direction;

							Color intersection_color = getColorAt(
									intersection_position,
									intersecting_ray_direction,
									index_of_winning_object, accuracy,
									ambientlight);

							tempRed[aa_index] =
									intersection_color.getColorRed();
							tempGreen[aa_index] =
									intersection_color.getColorGreen();
							tempBlue[aa_index] =
									intersection_color.getColorBlue();
						}
					}
				}
			}

			// average the pixel color
			double totalRed = 0;
			double totalGreen = 0;
			double totalBlue = 0;

			for (int iRed = 0; iRed < aadepth * aadepth; iRed++) {
				totalRed = totalRed + tempRed[iRed];
			}
			for (int iGreen = 0; iGreen < aadepth * aadepth; iGreen++) {
				totalGreen = totalGreen + tempGreen[iGreen];
			}
			for (int iBlue = 0; iBlue < aadepth * aadepth; iBlue++) {
				totalBlue = totalBlue + tempBlue[iBlue];
			}

			/* calculate pixel color */
			double avgRed = totalRed / (aadepth * aadepth);
			double avgGreen = totalGreen / (aadepth * aadepth);
			double avgBlue = totalBlue / (aadepth * aadepth);

			pixels[thisone].R = (int) floor(avgRed*255);
			pixels[thisone].G = (int) floor(avgGreen*255);
			pixels[thisone].B = (int) floor(avgBlue*255);

		}
	}

	image.writeImage(pixels);

	delete pixels;

}

RayTracer::~RayTracer() {
	// TODO Auto-generated destructor stub
}

/* read scene description !*/
bool RayTracer::readScene() {

	FILE *input = fopen(inputFile.c_str(), "r");

	/* file not found !*/
	if(input == NULL) {
		return false;
	}

	char name[100];
	int fscanfTrash;

	/* read Camera */
	fscanfTrash = fscanf(input, "%lf %lf %lf\n", &this->camera.campos.x,
			&this->camera.campos.y, &this->camera.campos.z);
	fscanfTrash = fscanf(input, "%lf %lf %lf\n", &this->camera.look_at.x,
			&this->camera.look_at.y, &this->camera.look_at.z);
	fscanfTrash = fscanf(input, "%lf %lf %lf\n", &this->camera.normal.x,
			&this->camera.normal.y, &this->camera.normal.z);
	fscanfTrash = fscanf(input, "%lf\n", &this->camera.eye_y);
	this->camera.setUp();

	/* read lights */
	int numberOfElements, i;
	Light light;
	Vect position;
	Color color;
	double aux;
	fscanfTrash = fscanf(input, "%d\n", &numberOfElements);
	for (i = 0; i < numberOfElements; i++) {
		fscanfTrash = fscanf(input, "%lf %lf %lf ", &position.x, &position.y,
				&position.z);
		fscanfTrash = fscanf(input, "%lf %lf %lf ", &color.red, &color.green,
				&color.blue);
		fscanfTrash = fscanf(input, "%lf %lf %lf\n", &color.special, &aux, &aux);

		light.position = position;
		light.color = color;
		this->light_sources.push_back(light);
	}

	/* read pigments */
	fscanfTrash = fscanf(input, "%d\n", &numberOfElements);
	for (i = 0; i < numberOfElements; i++) {
		fscanfTrash = fscanf(input, "%100s ", name);

		/* check pigment type */
		if(strcasecmp(name, "solid") == 0) {
			fscanfTrash = fscanf(input, "%lf %lf %lf\n", &color.red, &color.green, &color.blue); // solid color
			color.special = 0.25;
		}

		if(strcasecmp(name, "checker") == 0) {
			fscanfTrash = fscanf(input, "%lf %lf %lf ", &color.red, &color.green, &color.blue);
			color.special = 2;
			fscanfTrash = fscanf(input, "%lf %lf %lf %lf\n", &aux, &aux, &aux, &aux);
		}

		if(strcasecmp(name, "texmap") == 0) {
			color.red = color.green = color.blue = 0;
			color.special = 0.8;
			fscanfTrash = fscanf(input, "%100s\n", name);
			fscanfTrash = fscanf(input, "%lf %lf %lf %lf\n", &aux, &aux, &aux, &aux);
			fscanfTrash = fscanf(input, "%lf %lf %lf %lf\n", &aux, &aux, &aux, &aux);
		}

		pigments.push_back(color);
	}

	/* read extra */
	double reflection;
	fscanfTrash = fscanf(input, "%d\n", &numberOfElements);
	for (i = 0; i < numberOfElements; i++) {
		fscanfTrash = fscanf(input, "%lf %lf %lf %lf ", &reflection, &aux, &aux, &aux);
		this->object_properties.push_back(reflection);
		fscanfTrash = fscanf(input, "%lf %lf %lf\n", &aux, &aux, &aux);
	}

	/* read objects */
	Object object;
	int numberOfPlanes, j, pigment, properties;
	fscanfTrash = fscanf(input, "%d\n", &numberOfElements);
	for (i = 0; i < numberOfElements; i++) {

		fscanfTrash = fscanf(input, "%d %d %100s ", &pigment, &properties, name);

		/* set object pigment */
		object.color = this->pigments.at(pigment);

		/* decide object type */
		if (strcasecmp(name, "sphere") == 0) {
			object.type = SPHERE;
			fscanfTrash = fscanf(input, "%lf %lf %lf %lf\n", &object.center.x, &object.center.y,
					&object.center.z, &object.radius);
		}

		/* poliedro */
		else{
			fscanfTrash = fscanf(input, "%d\n", &numberOfPlanes);
			for(j=0 ; j < numberOfPlanes ; j++) {
				object.type = PLANE;
				object.distance = -1;
				fscanfTrash = fscanf(input, "%lf %lf %lf %lf\n", &object.normal.x, &object.normal.y, &object.normal.z, &aux);
			}
		}
		scene_objects.push_back(object);
	}

	fclose(input);
	/* file was read successfully! */
	return true;
}

int RayTracer::winningObjectIndex(vector<double> object_intersections) {
	// return the index of the winning intersection
	int index_of_minimum_value = 0;

	// prevent unnessary calculations
	if (object_intersections.size() == 0) {
		// if there are no intersections
		return -1;
	} else if (object_intersections.size() == 1) {
		if (object_intersections.at(0) > 0) {
			// if that intersection is greater than zero then its our index of minimum value
			return 0;
		} else {
			// otherwise the only intersection value is negative
			return -1;
		}
	} else {
		// otherwise there is more than one intersection
		// first find the maximum value

		double max = 0;
		for (size_t i = 0; i < object_intersections.size(); i++) {
			if (max < object_intersections.at(i)) {
				max = object_intersections.at(i);
			}
		}

		// then starting from the maximum value find the minimum positive value
		if (max > 0) {
			// we only want positive intersections
			for (size_t index = 0; index < object_intersections.size(); index++) {
				if (object_intersections.at(index) > 0
						&& object_intersections.at(index) <= max) {
					max = object_intersections.at(index);
					index_of_minimum_value = index;
				}
			}

			return index_of_minimum_value;
		} else {
			// all the intersections were negative
			return -1;
		}
	}
}

Color RayTracer::getColorAt(Vect intersection_position,
		Vect intersecting_ray_direction, int index_of_winning_object,
		double accuracy, double ambientlight) {

	Color winning_object_color =
			scene_objects.at(index_of_winning_object).getColor();
	Vect winning_object_normal =
			scene_objects.at(index_of_winning_object).getNormalAt(
					intersection_position);

	if (winning_object_color.getColorSpecial() == 2) {
		// checkered/tile floor pattern

		int square = (int) floor(intersection_position.getVectX())
				+ (int) floor(intersection_position.getVectZ());

		if ((square % 2) == 0) {
			// black tile
			winning_object_color.setColorRed(0);
			winning_object_color.setColorGreen(0);
			winning_object_color.setColorBlue(0);
		} else {
			// white tile
			winning_object_color.setColorRed(1);
			winning_object_color.setColorGreen(1);
			winning_object_color.setColorRed(1);
		}
	}

	Color final_color = winning_object_color.colorScalar(ambientlight);

	if (winning_object_color.getColorSpecial() > 0
			&& winning_object_color.getColorSpecial() <= 1) {
		// reflection from objects with specular intensity
		double dot1 = winning_object_normal.dotProduct(
				intersecting_ray_direction.negative());
		Vect scalar1 = winning_object_normal.vectMult(dot1);
		Vect add1 = scalar1.vectAdd(intersecting_ray_direction);
		Vect scalar2 = add1.vectMult(2);
		Vect add2 = intersecting_ray_direction.negative().vectAdd(scalar2);
		Vect reflection_direction = add2.normalize();

		Ray reflection_ray(intersection_position, reflection_direction);

		// determine what the ray intersects with first
		vector<double> reflection_intersections;

		for (size_t reflection_index = 0; reflection_index < scene_objects.size();
				reflection_index++) {
			reflection_intersections.push_back(
					scene_objects.at(reflection_index).findIntersection(
							reflection_ray));
		}

		int index_of_winning_object_with_reflection = winningObjectIndex(
				reflection_intersections);

		if (index_of_winning_object_with_reflection != -1) {
			// reflection ray missed everthing else
			if (reflection_intersections.at(
					index_of_winning_object_with_reflection) > accuracy) {
				// determine the position and direction at the point of intersection with the reflection ray
				// the ray only affects the color if it reflected off something

				Vect reflection_intersection_position =
						intersection_position.vectAdd(
								reflection_direction.vectMult(
										reflection_intersections.at(
												index_of_winning_object_with_reflection)));
				Vect reflection_intersection_ray_direction =
						reflection_direction;

				Color reflection_intersection_color = getColorAt(
						reflection_intersection_position,
						reflection_intersection_ray_direction,
						index_of_winning_object_with_reflection, accuracy,
						ambientlight);

				final_color = final_color.colorAdd(
						reflection_intersection_color.colorScalar(
								winning_object_color.getColorSpecial()));
			}
		}
	}

	for (size_t light_index = 0; light_index < light_sources.size();
			light_index++) {
		Vect light_direction =
				light_sources.at(light_index).getLightPosition().vectAdd(
						intersection_position.negative()).normalize();

		float cosine_angle = winning_object_normal.dotProduct(light_direction);

		if (cosine_angle > 0) {
			// test for shadows
			bool shadowed = false;

			Vect distance_to_light =
					light_sources.at(light_index).getLightPosition().vectAdd(
							intersection_position.negative()).normalize();
			float distance_to_light_magnitude = distance_to_light.magnitude();

			Ray shadow_ray(intersection_position,
					light_sources.at(light_index).getLightPosition().vectAdd(
							intersection_position.negative()).normalize());

			vector<double> secondary_intersections;

			for (size_t object_index = 0;
					object_index < scene_objects.size() && shadowed == false;
					object_index++) {
				secondary_intersections.push_back(
						scene_objects.at(object_index).findIntersection(
								shadow_ray));
			}

			for (size_t c = 0; c < secondary_intersections.size(); c++) {
				if (secondary_intersections.at(c) > accuracy) {
					if (secondary_intersections.at(c)
							<= distance_to_light_magnitude) {
						shadowed = true;
					}
				}
				break;
			}

			if (shadowed == false) {
				final_color =
						final_color.colorAdd(
								winning_object_color.colorMultiply(
										light_sources.at(light_index).getLightColor()).colorScalar(
										cosine_angle));

				if (winning_object_color.getColorSpecial() > 0
						&& winning_object_color.getColorSpecial() <= 1) {
					// special [0-1]
					double dot1 = winning_object_normal.dotProduct(
							intersecting_ray_direction.negative());
					Vect scalar1 = winning_object_normal.vectMult(dot1);
					Vect add1 = scalar1.vectAdd(intersecting_ray_direction);
					Vect scalar2 = add1.vectMult(2);
					Vect add2 = intersecting_ray_direction.negative().vectAdd(
							scalar2);
					Vect reflection_direction = add2.normalize();

					double specular = reflection_direction.dotProduct(
							light_direction);
					if (specular > 0) {
						specular = pow(specular, 10);
						final_color =
								final_color.colorAdd(
										light_sources.at(light_index).getLightColor().colorScalar(
												specular
														* winning_object_color.getColorSpecial()));
					}
				}

			}

		}
	}

	return final_color.clip();
}
