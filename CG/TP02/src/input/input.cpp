#include <GL/glut.h>
#include "../rendering/rendering.h"
#include "input.h"

/* process keyboard input. receives key and mouse position */
void processNormalInput(unsigned char key, int x, int y) {

	// esc key code
	if (key == ESC_KEY_CODE) {
		exit(0);
	}

}

void processSpecialKeys(int key, int x, int y) {

}

/* processa clicks do mouse */
void processMouseClick(int button, int state, int x, int y) {

	// seleciona eventos 'key up'
	if (state == GLUT_UP) {

		// pausa ou despausa o jogo
		if (button == GLUT_RIGHT_BUTTON) {
		}

		// dispara missel
		if (button == GLUT_LEFT_BUTTON) {
		}

		if (button == GLUT_MIDDLE_BUTTON) {
		}

	}
}
