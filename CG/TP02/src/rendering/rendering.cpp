/*
 * rendering.cpp
 *
 implement opengl callbacks and rendering functions
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

/* world, flock and camera */
World w;
Flock bflock(w.getTowerHeight(), w.getWorldSize());
Camera camera(Vector(10, 5, 50), Vector(0, 0, 0), Vector(0, 1, 0),
		w.getTowerHeight());

/* control variables */
int debug = 0;
bool nextFrame = false;
bool fog_enabled = false;
bool started = false;
float fog_density = FOG_DENSITY;

/* buffer de interface do usuario */
char hud_buffer[100];

// Desenha um texto na janela GLUT
void draw_text(char *string, float x, float y) {
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0.0, screenWidth, 0.0, screenHeight);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	// Posição no universo onde o texto será colocado
	glRasterPos2f(x, y);

	// Exibe caracter a caracter
	while (*string) {
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *string++);
	}

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
}

/* display callback function */
void render_scene() {

	/* Limpar todos os pixels */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (started) {
		camera.look_at();
		w.draw_world();
		bflock.draw_boids();
	}
	else {
		draw_text("- cubieboids -", screenWidth / 2, screenHeight / 2);
		draw_text("press 's' to start!", screenWidth / 2, screenHeight / 2 - 20);
	}

	/* Não esperar! */
	glFlush();

}

/* program main loop */
void main_loop(int data) {

	glutTimerFunc(REFRESH_RATE, main_loop, 1);

	if (started) {
		/* check if debug mode is active */
		if (!debug || nextFrame) {
			camera.update_camera(bflock.flock_center, bflock.leader.speed);
			bflock.update_boids(w.get_objects());
		}
		if (debug && nextFrame) {
			bflock.debug_flock();
			w.debug_world();
			camera.debug_camera();
			nextFrame = false;
		}
	}

	/* redraw scene */
	glutPostRedisplay();
}

/* enable OpenGL fog engine */
void enable_fog() {

	GLfloat density = fog_density;

	GLfloat fogColor[4] = { 0.5, 0.5, 0.5, 1.0 };

	glEnable(GL_FOG);
	glFogi(GL_FOG_MODE, GL_EXP2);
	glFogfv(GL_FOG_COLOR, fogColor);
	glFogf(GL_FOG_DENSITY, density);
	glHint(GL_FOG_HINT, GL_NICEST);

}

/* disable fog */
void disable_fog() {

	glDisable(GL_FOG);

}

/* process keyboard input. receives key and mouse position */
void processNormalInput(unsigned char key, int x, int y) {

	// esc key code
	if (key == ESC_KEY_CODE) {
		exit(0);
	}

	/* change camera mode */
	if (key == 'c') {
		camera.change_mode();
	}

	/* add new boid to flock */
	if (key == 'a') {
		bflock.add_new_boid();
	}

	/* remove boid from flock */
	if (key == 'r') {
		bflock.remove_boid();
	}

	/* camera zoom-in, zoom-out */
	if (key == 'q') {
		camera.zoom(ZOOM_OUT);
	}

	if (key == 'e') {
		camera.zoom(ZOOM_IN);
	}

	/* activate debug mode */
	if (key == 'd') {
		debug = (debug + 1) % 2;
		nextFrame = true;
	}

	/* start simulation */
	if (key == 's') {
		started = true;
	}

	/* advance frame */
	if (key == 'n') {
		nextFrame = true;
	}

	/* enable-disable fog */
	if (key == 'f') {
		if (fog_enabled) {
			disable_fog();
			fog_enabled = false;
		} else {
			enable_fog();
			fog_enabled = true;
		}
	}

}
/* process keyboard special keys inputs */
void processSpecialKeys(int key, int x, int y) {

	/* turn flock leader */
	if (key == GLUT_KEY_LEFT) {
		bflock.direct_boid_leader(LEFT);
	}
	if (key == GLUT_KEY_RIGHT) {
		bflock.direct_boid_leader(RIGHT);
	}
	if (key == GLUT_KEY_UP) {
		bflock.direct_boid_leader(UP);
	}
	if (key == GLUT_KEY_DOWN) {
		bflock.direct_boid_leader(DOWN);
	}

	/* change fog density */
	if (key == GLUT_KEY_F1) {
		fog_density -= 0.00001;
		enable_fog();
		printf("# Fog Density: %3f\n", fog_density);
	}
	if (key == GLUT_KEY_F2) {
		fog_density += 0.00001;
		enable_fog();
		printf("# Fog Density: %3f\n", fog_density);
	}

}

/* init OpenGL lighting engine */
void init_lighting() {

	// clear depth buffer
	glClearDepth(1);
	// enable depth testing
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);

}

/* init rendering variables */
void init_rendering(int argc, char** argv) {

	// init window size
	processArguments(argc, argv);

	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(screenWidth, screenHeight);
	glutCreateWindow("Cubie-boids");

	/* init lighting */
	init_lighting();

	// register callback functions
	register_callbacks();

}

/* processa argumentos recebidos pelo programa */
void processArguments(int argc, char** argv) {
	// check program arguments
	if (argc != 3) {
		printf(
				"Erro de parametros! Uso: ./cubieboids <SCREEN WIDTH> <SCREEN HEIGHT>\n");
		printf(
				"Usando paremtros padrao! SCREEN WIDTH: 800 - SCREEN HEIGHT: 600\n");
		screenWidth = DEFAULT_WIDTH;
		screenHeight = DEFAULT_HEIGHT;
	} else {
		// get screen width and height
		screenWidth = atoi(argv[1]);
		screenHeight = atoi(argv[2]);
	}
}

/* callback function for window resizing */
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
}
