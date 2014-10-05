#include "object.h"
#include "../math/math.c"

/* pinta object com determinada cor definida no arquivo colors.c */
void paint_object(object *s, int color) {
	if( color == RED ) {
		s->color = &red[0];
		return;
	}
	if( color == GREEN ) {
		s->color = &green[0];
		return;
	}
	if( color == WHITE ) {
		s->color = &white[0];
		return;
	}
	if( color == YELLOW ) {
		s->color = &yellow[0];
		return;
	}
	if( color == BLUE ) {
		s->color = &blue[0];
		return;
	}
}

void update_object_position(object *s) {
	s->x += s->x_speed;
	s->y += s->y_speed;
}

/* calcula se objeto esta fora da tela no eixo x */
boolean x_out_of_bounds(object *s, int screenWidth) {
	
	if( s->x - s->size < 0 || s->x + s->size > screenWidth )
		return TRUE;
	
	return FALSE;
}

/* calcula se objeto esta fora da tela no eixo y */
boolean y_out_of_bounds(object *s, int screenHeight) {
	
	if( s->y - s->size < 0 || s->y + s->size > screenHeight )
		return TRUE;
		
	return FALSE;
}

/* detecta colisao do tipo bounding box entre um objeto 'a'
 * e um objeto 'b' */
boolean detect_boundbox_collision(object *a, object *b) {
	
	float distance_ab = distance(a->x, a->y, b->x, b->y);
	
	if( distance_ab < (a->size + b->size) ) {
		return TRUE;
	}
	else {
		return FALSE;
	}
}

