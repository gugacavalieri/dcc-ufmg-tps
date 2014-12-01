/*
 * rendering.h
 *
 */

#ifndef RENDERING_RENDERING_H_
#define RENDERING_RENDERING_H_

#define DEFAULT_WIDTH 800
#define DEFAULT_HEIGHT 600
#define ESC_KEY_CODE 27
#define REFRESH_RATE 15 // screen refresh rate (mseconds)

#define FOG_DENSITY 0.00025f

void main_loop(int data);

/* rendering methods */

/* display callback function */
void render_scene();
/* program main loop */
void main_loop(int data);
/* enable OpenGL fog engine */
void enable_fog();
/* disable fog */
void disable_fog();
/* process keyboard input. receives key and mouse position */
void processNormalInput(unsigned char key, int x, int y);
/* process keyboard special keys inputs */
void processSpecialKeys(int key, int x, int y);
/* init OpenGL lighting engine */
void init_lighting();
/* init rendering variables */
void init_rendering(int argc, char** argv);
/* processa argumentos recebidos pelo programa */
void processArguments(int argc, char** argv);
/* callback function for window resizing */
void reshape(int w, int h);
/* register callback functions */
void register_callbacks();


#endif /* RENDERING_RENDERING_H_ */
