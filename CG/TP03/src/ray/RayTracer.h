/*
 * RayTracer.h
 *
 *  Created on: Nov 27, 2014
 *      Author: gustavo
 */

#ifndef SRC_RAY_RAYTRACER_H_
#define SRC_RAY_RAYTRACER_H_

#define MIN_ACCURACY 0.00000001
#define AMBIENT_LIGHT 0.2

#include <string>
#include <vector>
#include "../object/Object.h"
#include "../img/Image.h"
#include "../img/Pixel.h"
#include "../camera/Camera.h"
#include "../light/Light.h"

using namespace std;

struct RGBType {
	double r;
	double g;
	double b;
};

class RayTracer {
public:

	string inputFile;

	RayTracer(int screenWidth, int screenHeight, string outputFile,
			string inputFile) :
			image(screenWidth, screenHeight, outputFile) {
		this->inputFile = inputFile;
	}

	void start();
	bool readScene();
	int winningObjectIndex(vector<double> object_intersections);
	Color getColorAt(Vect intersection_position,
			Vect intersecting_ray_direction, int index_of_winning_object,
			double accuracy, double ambientlight);
	void savebmp(const char *filename, int w, int h, int dpi, RGBType *data);

	RayTracer();
	virtual ~RayTracer();

private:

	Image image;
	Camera camera;
	vector<Object> scene_objects;
	vector<Light> light_sources;
	vector<Color> pigments;
	vector<double> object_properties;

};

#endif /* SRC_RAY_RAYTRACER_H_ */
