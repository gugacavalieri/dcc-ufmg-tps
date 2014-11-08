#include <GL/glut.h>
#include "../rendering/rendering.h"
#include "input.h"

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
