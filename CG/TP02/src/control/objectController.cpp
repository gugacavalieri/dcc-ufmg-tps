/*
 * objectController.cpp
 *
 */

#include <GL/glut.h>
#include "objectController.h"


void main_loop(int data) {

	glutTimerFunc(REFRESH_RATE, main_loop, 1);

	glutPostRedisplay();
}

