#include <stdio.h>
#include <stdlib.h>

#define MOUSE_BAR_MOTION_SIZE 80
#define HUD_POSITION 40
#define WINDOW_NAME "OpenGalaxian"

/* buffer de interface do usuario */
char hud_buffer[100];

/* desenha barra de movimentacao do mouse */
void draw_mouse_motion(int x) {
	
	/* escolhe cor da barra */
	glColor3f(yellow[0], yellow[1], yellow[2]);
	
	/* calcula tamanho da barra */
	float bar_size = (float) screenHeight / MOUSE_BAR_MOTION_SIZE;

	/* draw it ! */
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

/* desenha interface do usuario */
void draw_hud() {
	/* calcula posicao da hud */
	float hud_y = (float) (screenHeight - (float)screenHeight / HUD_POSITION);
	/* imprime valores no hud buffer */
	sprintf(hud_buffer, " ---------- open galaxian ---------- score: %d ---------- wave: %d ----------", score, enemies.wave);
	/* desenha hud */
	draw_text( hud_buffer, 0, hud_y);
	
}

/* desenha frame da cena de acordo com as variaveis de estado do jogo */
void renderScene(void) {
	
	/* Limpar todos os pixels */
	glClear (GL_COLOR_BUFFER_BIT);
	
	/* frame de jogo */
	if ( !game_over && start && !win) {
		draw_objects();
		draw_mouse_motion(mouse_x);
		draw_hud();
	}
	/* titulo inicial */
	if ( !start ) {
			draw_text("open galaxian . clique para iniciar", middle_x, middle_y);
	}
	/* game over title */
	if( game_over )
		draw_text("GAME OVER! Aperte 'r' para reiniciar!", middle_x, middle_y);
	/* frame da vitoria !*/
	if( win ) {
		draw_text("Voce derrotou o esquadrao alienigena!", middle_x, middle_y);
		draw_text("Aperte 'r' para reiniciar!", middle_x, middle_y - 30);
	}
	
	/* Não esperar! */
	glFlush ();

}

/* recalcula propocoes quando a janela eh redimensionada */
void windowResize(int width, int height) {
	
	screenWidth = width;
	screenHeight = height;
	calculate_screen_variables();

	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0,0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,width,0,height);
	
}

/* checa se um determinado valor esta dentro dos limites especificados */
boolean checkBoundaries(int position, int lower_bound, int higher_bound) {

	if( position > lower_bound && position < higher_bound) 
		return TRUE;
	else
		return FALSE;
}
