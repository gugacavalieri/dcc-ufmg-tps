#include <stdio.h>
#include <stdlib.h>

#define ESC_KEY_CODE 27

/* process program received arguments */
void processProgramArguments(int argc, char **argv) {
		
		// check program arguments
		if(argc != 3) {
			printf("Erro de parametros! Uso: ./galaxian <SCREEN WIDTH> <SCREEN HEIGHT>\n");
			exit(0);
		}
		else{
			// get screen width and height
			screenWidth = atoi(argv[1]);
			screenHeight = atoi(argv[2]);
		}
	
}

/* process keyboard input. receives key and mouse position */
void processNormalInput(unsigned char key, int x, int y) {
	
	if( ! paused ){
		// esc key code
		if(key == ESC_KEY_CODE) {
			clean_up();
			exit(0);
		}
		
		if(key == 'r') {
			// ... restart game
			restart();
		}
	}
}

void processSpecialKeys(int key, int x, int y) {

	
}

void processMouseClick(int button, int state, int x, int y) {

	// seleciona eventos 'key up'
	if( state == GLUT_UP ) {
		
		// pausa ou despausa o jogo
		if( button == GLUT_RIGHT_BUTTON ) {
			paused = (paused + 1) % 2;
		}
			
		// dispara missel
		if( button == GLUT_LEFT_BUTTON ) {
			new_bullet(main_spaceship.x, main_spaceship.y + main_spaceship.size, UP);
			start = TRUE;
		}
		
		if( button == GLUT_MIDDLE_BUTTON ) {
			paused = (paused + 1) % 2 ;
			debug_game();
		}
			
	}
}

void mouseMotion(int x, int y) {


	int diff_mouse_pos = x - middle_x;
	float pace = (float) diff_mouse_pos / SPEED_FACTOR;
	
	/* atualiza velocidade da object */
	main_spaceship.x_speed = pace;
	
	/* atualiza posicao do mouse */
	mouse_x = x;
	
}
