/*
 * main.cpp
 *
 *  Created on: Oct 25, 2014
 *      Author: gustavo
 */
#include <GL/glut.h>

#include "rendering/rendering.h"
#include "control/objectController.h"

int main(int argc, char **argv) {

	init_rendering(argc, argv);

	// game loop at refresh rate = 60Hz
	glutTimerFunc(REFRESH_RATE, main_loop, 1);

	// enter GLUT event processing cycle
	glutMainLoop();

}

