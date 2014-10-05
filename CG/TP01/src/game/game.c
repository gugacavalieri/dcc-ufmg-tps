#define LEFT -1
#define RIGHT 1
#define UP 2
#define DOWN -2

#define SPEED_FACTOR 50
#define REFRESH_RATE 15


#include "../rendering/colors.c"
#include "../models/object.c"
#include "../models/list.c"
#include "objectController.c"
#include "debug.c"


/* screen variables */
int screenWidth, screenHeight;
float middle_x, middle_y;
float mouse_x;

/* game variables */
boolean paused;
boolean debug;
boolean start;

/*
 *FUNCTIONS 
 */
 
 void calculate_screen_variables() {
	middle_x = (float) screenWidth / 2;
	middle_y = (float) screenHeight / 2;
}

/* inicializa as variaveis do jogo */
void initGlobal() {
	
	/* selecionar cor de fundo (preto)*/
	glClearColor (0.0, 0.0, 0.0, 0.0);

	/* inicializar sistema de viz. */
	glViewport(0,0,screenWidth,screenHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(0.0, screenWidth, 0.0, screenHeight, -1.0, 1.0);
	gluOrtho2D(0, screenWidth, 0, screenHeight);
	
	/* inicializa as variaveis */
	init_controller(screenWidth, screenHeight);
	
	calculate_screen_variables();
	
	paused = FALSE;
	start = FALSE;
	
}



/* reinicia o jogo **/
void restart() {
	clean_up();
	initGlobal();
}

/* game loop principal */
void gameLoop(int data) {
	
	glutTimerFunc(REFRESH_RATE, gameLoop, 1);
	
	/* se nao pausado, atualiza as variaveis e redesenha a tela */
	if( ! paused && start ) {
		
		if( ! game_over ){ 
			update_objects(screenWidth, screenHeight);
		}
		
	}
	
	glutPostRedisplay();
		
}
