#include <stdio.h>
#include <stdlib.h>

#define MOUSE_BAR_MOTION_SIZE 80
#define HUD_POSITION 40
#define WINDOW_NAME "OpenGalaxian"

char hud_buffer[100];

void draw_mouse_motion(int x) {
	
	glColor3f(yellow[0], yellow[1], yellow[2]);
	
	float bar_size = (float) screenHeight / MOUSE_BAR_MOTION_SIZE;

	glBegin(GL_QUADS);
		glVertex3f( middle_x , 0.0f  , 0.0f);
		glVertex3f( x , 0.0f , 0.0f);
		glVertex3f( x , bar_size , 0.0f);
		glVertex3f( middle_x , bar_size , 0.0f);
	glEnd();
}

// Desenha um texto na janela GLUT
void draw_text(char *string, float x, float y) 
{  
  	glPushMatrix();
    // Posição no universo onde o texto será colocado          
    glRasterPos2f(x, y); 
    // Exibe caracter a caracter
    while(*string) {
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,*string++); 
	}
	glPopMatrix();
}

void draw_hud() {
	/* calcula posicao da hud */
	float hud_y = (float) (screenHeight - (float)screenHeight / HUD_POSITION);
	/* imprime valores no hud buffer */
	sprintf(hud_buffer, " ---------- open galaxian ---------- score: %d ---------- wave: %d ----------", score, enemies.wave);
	/* desenha hud */
	draw_text( hud_buffer, 0, hud_y);
	
}

void renderScene(void) {
	
	/* Limpar todos os pixels */
	glClear (GL_COLOR_BUFFER_BIT);
	
	if ( !game_over && start ) {
		draw_objects();
		draw_mouse_motion(mouse_x);
		draw_hud();
	}
	if ( !start ) {
			draw_text("open galaxian . clique para iniciar", middle_x, middle_y);
	}
	if( game_over )
		draw_text("GAME OVER! Aperte 'r' para reiniciar!", middle_x, middle_y);
	
	/* Não esperar! */
	glFlush ();

}

void windowResize(int width, int height) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(height == 0)
		height = 1;
	float ratio = 1.0* width / height;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

    // Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, width, height);

	// Set the correct perspective.
	gluPerspective(45,ratio,1,1000);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
	
}

/* checa se um determinado valor esta dentro dos limites especificados */
boolean checkBoundaries(int position, int lower_bound, int higher_bound) {

	if( position > lower_bound && position < higher_bound) 
		return TRUE;
	else
		return FALSE;
}
