#define BULLET_SIZE 400
#define BULLET_SPEED 2.0f

/* print out object variables */
void debug_bullet(object *s) {
	
	printf("bullet coordinates: (%f,%f), speed: (%f,%f)\n", s->x, s->y, s->x_speed, s->y_speed);
	
}

/* initiate bullet variables */
void init_bullet(object *s, int x, int y, int direction, float size) {

	// inicia variaveis de posicao e tamanho
	s->x = (float) x;
	s->y = (float) y;
	s->size = size;
	
	// verifica direcao
	if( direction == UP )
		s->y_speed = BULLET_SPEED;
	else
		s->y_speed = -BULLET_SPEED;
		
	s->x_speed = 0;
	
	paint_object(s, BLUE);
	
}

/* desenha um missel ! */
void draw_bullet(object *s) {
	
	glColor3f(s->color[0], s->color[1], s->color[2]);

	glBegin(GL_QUADS);
		glVertex3f( s->x - s->size, s->y - s->size , 0.0f);
		glVertex3f( s->x + s->size, s->y - s->size , 0.0f);
		glVertex3f( s->x + s->size, s->y + s->size , 0.0f);
		glVertex3f( s->x - s->size, s->y + s->size , 0.0f);
	glEnd();
}

