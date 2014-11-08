/*
 * rendering.cpp
 *
 */

#include <GL/glut.h>
#include <stdio.h>
#include "rendering.h"
#include "../camera/Camera.h"
#include "../model/Flock.h"
#include "../model/World.h"
#include "../util/vector.h"

/* rendering variables */
int screenWidth, screenHeight;
float window_aspect;

World w;
Flock bflock(w.getTowerHeight(), w.getWorldSize());
Camera camera(Vector(10, 5, 50), Vector(0, 0, 0), Vector(0, 1, 0),
		w.getTowerHeight());

void render_scene() {

	/* Limpar todos os pixels */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	camera.update_camera(bflock.flock_center, bflock.leader.speed);
	camera.look_at();

	bflock.update_boids();
	bflock.draw_boids();

	w.draw_world();

	/* Não esperar! */
	glFlush();

}

/* process keyboard input. receives key and mouse position */
void processNormalInput(unsigned char key, int x, int y) {

	// esc key code
	if (key == ESC_KEY_CODE) {
		exit(0);
	}

	if (key == 'c') {
		camera.change_mode();
	}

	/* add new boid to flock */
	if (key == 'a') {
		bflock.add_new_boid();
	}

	/* remove boid from flock */
	if(key == 'r') {
		bflock.remove_boid();
	}

	if(key == 'q') {
		camera.zoom(ZOOM_OUT);
	}

	if(key == 'e') {
		camera.zoom(ZOOM_IN);
	}

}

void processSpecialKeys(int key, int x, int y) {

	/* turn flock leader */
	if( key == GLUT_KEY_LEFT ) {
		bflock.direct_boid_leader(LEFT);
	}
	if( key == GLUT_KEY_RIGHT ) {
		bflock.direct_boid_leader(RIGHT);
	}
	if( key == GLUT_KEY_UP ) {
		bflock.direct_boid_leader(UP);
	}
	if( key == GLUT_KEY_DOWN ) {
		bflock.direct_boid_leader(DOWN);
	}

}


void init_lighting() {

	// clear depth buffer
	glClearDepth(1);
	// enable depth testing
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);

}

void init_rendering(int argc, char** argv) {

	// init window size
	processArguments(argc, argv);

	// set window aspect
	camera.set_window_aspect((float) screenWidth / screenHeight);

	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(screenWidth, screenHeight);
	glutCreateWindow("VBoids");

	init_lighting();

	bflock.add_new_boid();

	// register callback functions
	register_callbacks();

}

/* processa argumentos recebidos pelo programa */
void processArguments(int argc, char** argv) {
	// check program arguments
	if (argc != 3) {
		printf("Erro de parametros! Uso: ./galaxian <SCREEN WIDTH> <SCREEN HEIGHT>\n");
		printf("Usando paremtros padrao! SCREEN WIDTH: 800 - SCREEN HEIGHT: 600\n");
		screenWidth = DEFAULT_WIDTH;
		screenHeight = DEFAULT_HEIGHT;
	} else {
		// get screen width and height
		screenWidth = atoi(argv[1]);
		screenHeight = atoi(argv[2]);
	}
}

void reshape(int w, int h) {

	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20000.0);
	glMatrixMode(GL_MODELVIEW);

}

/* register callback functions */
void register_callbacks() {
	glutDisplayFunc(render_scene);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(processNormalInput);
	glutSpecialFunc(processSpecialKeys);
//	glutPassiveMotionFunc (mouseMotion);
//	glutMouseFunc(processMouseClick);
}
