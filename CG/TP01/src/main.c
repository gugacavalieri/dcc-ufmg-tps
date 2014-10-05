/* open gl - glut libraries */
#include <GL/glut.h>

/* global variables and models */
#include "game/game.c"
/* callback definitions */
#include "rendering/rendering.c"
#include "input/input.c"

int main(int argc, char **argv) {

	processProgramArguments(argc, argv);
	
	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(screenWidth,screenHeight);
	glutCreateWindow(WINDOW_NAME);

	initGlobal();
	
	// register callbacks
	glutDisplayFunc(renderScene);
	//glutReshapeFunc(windowResize);
	glutKeyboardFunc(processNormalInput);
	glutSpecialFunc(processSpecialKeys);
	glutPassiveMotionFunc(mouseMotion);
	glutMouseFunc(processMouseClick);
	
	// game loop at refresh rate = 60Hz
	glutTimerFunc(REFRESH_RATE, gameLoop, 1);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}
