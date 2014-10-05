#define PACE 20

#define SPACESHIP_SIZE 70
#define ALIEN_SIZE 80
#define ALIEN_X_SPEED 0.5f
#define ALIEN_Y_SPEED -0.2f

/* print out object variables */
void debug_spaceship(object *s) {
	
	printf("spaceship coordinates: (%f,%f), Speed: (%f,%f)\n", s->x, s->y, s->x_speed, s->y_speed);
	
}

/* print out object variables */
void debug_alien(object *s, float squad_x_speed, float squad_y_speed) {
	
	float x_speed = s->x_speed + squad_x_speed;
	float y_speed = s->y_speed + squad_y_speed;
	
	printf("Alien coordinates: (%f,%f), Speed: (%f,%f)\n", s->x, s->y, x_speed, y_speed);
	
}

/* initiate object variables */
void init_spaceship(object *s, int screenWidth, int screenHeight, float size, int color) {
	
	s->x = (float) screenWidth / 2;
	s->y = (float) screenHeight / 18;
	
	s->size = size;
	
	paint_object(s, color);
}

/* desenha espaconave principal */
void draw_spaceship(object *s) { 
	
	glColor3f(s->color[0], s->color[1], s->color[2]);

	glBegin(GL_TRIANGLES);
		glVertex3f( s->x - s->size, s->y - s->size , 0.0f);
		glVertex3f( s->x + s->size, s->y - s->size , 0.0f);
		glVertex3f( s->x , s->y + s->size , 0.0f);
	glEnd();
	
}

/* inicializa as variaveis do alien */
void init_alien(object *s, float x, float y, float size, int color) {
	/* variaveis de posição e tamanho */
	s->x = x;
	s->y = y;
	s->size = size;
	/* velocidade determinada pelo esquadrao ! */
	s->x_speed = 0;
	s->y_speed = 0;
	/* pinta o alien !*/
	paint_object(s, color);
	
}
/* desenha um alien */
void draw_alien(object *s) {
	
	glColor3f(s->color[0], s->color[1], s->color[2]);

	glBegin(GL_TRIANGLES);
		glVertex3f( s->x - s->size, s->y + s->size , 0.0f);
		glVertex3f( s->x + s->size, s->y + s->size , 0.0f);
		glVertex3f( s->x , s->y - s->size , 0.0f);
	glEnd();
	
}

/* atualiza variaveis da nave principal */
void update_spaceship(object *s, int lower_bound, int higher_bound) {
	
	int new_position;
	
	if(s->x_speed > 0)
		new_position = (int) (s->x + s->size + s->x_speed);
	else
		new_position = (int) (s->x - s->size + s->x_speed);
	
	if( checkBoundaries(new_position, lower_bound, higher_bound) ) {
		s->x += s->x_speed;
	}
}

/* verifica se um ponto 'p' esta dentro de um objeto espaconave
 * funcao utilizada para detectar colisoes
 */
boolean spaceship_collision(object *s, float p1, float p2, int type) {
	
	boolean b1, b2, b3;
	
	/* verifica a orientacao do ponto atraves dos segmentos de reta do triangulo */
	b1 = sign(p1,p2, (s->x - s->size),(s->y - s->size), (s->x + s->size),(s->y - s->size)) < 0.0f;
	b2 = sign(p1,p2, (s->x + s->size),(s->y - s->size), (s->x),(s->y + s->size)) < 0.0f;
	b3 = sign(p1,p2, (s->x),(s->y + s->size), (s->x - s->size),(s->y - s->size)) < 0.0f;
	
	if( (b1 == b2) && (b2 == b3) ) {
		return TRUE;
	}
	else {
		return FALSE;
	}
}

void explode(object *s) {
	
}

