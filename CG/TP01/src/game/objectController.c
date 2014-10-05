#include "../models/spaceship.c"
#include "../models/bullet.c"
#include "../models/squad.c"

#define KILL_POINTS 100
#define MAX_WAVES 3

object main_spaceship;
squad enemies;
list bullets;

float bullet_size;
float spaceship_size;

int score;

boolean game_over;
boolean win;

/* free memory allocated */
void clean_up() {
	
	clear_squad(&enemies);
	clear_list(&bullets);
	
}

/* inicializa as variaveis do controlador */
void init_controller (int screenWidth, int screenHeight) {
	
	/* inicializa a lista de inimigos e bombas */
	init_squad(&enemies, screenWidth, screenHeight);
	init_list(&bullets);
	
	/* inicializa variaveis de  proporcao */
	bullet_size = (float) screenHeight / BULLET_SIZE;
	spaceship_size = (float) screenHeight / SPACESHIP_SIZE;
	game_over = FALSE;
	win = FALSE;
	score = 0;
	
	/* inicializa a nave principal */
	init_spaceship(&main_spaceship, screenWidth, screenHeight, spaceship_size, WHITE);
	/* inicializa inimigos */
	generate_squad(&enemies, screenWidth);
}

/* debuga as variaveis do controlador */
void debug_controller () {
	
}

/* instancia nova bullet e a adiciona a lista */
void new_bullet(int x, int y, int direction) {
	object bullet;
	init_bullet(&bullet, x, y, direction, bullet_size);
	insert(&bullets, bullet);
}

boolean check_collision_bullets(object *s, list *bullets, int bullets_direction) {
	
	/* list iterator */
	node_pointer iterator = get_first_element(bullets);
	
	while( iterator != NULL ) {
		
		if( bullets_direction == UP ) {
			/* check for bullets going UP only */
			if( iterator->o.y_speed > 0 ) {
				/* check for collision */
				if( detect_boundbox_collision(s, &iterator->o) ) {
					remove_item(iterator, bullets);
					return TRUE;
				}
			}
		}
		else{
			/* check for bullets going DOWN only */
			if( iterator->o.y_speed < 0 ) {
				/* check for collision */
				if( detect_boundbox_collision(s, &iterator->o) ) {
					remove_item(iterator, bullets);
					return TRUE;
				}
			}
		}
		
		iterator = iterator->next;
	}
	return FALSE;
}

void update_squad(squad *s, list *bullets, int screenWidth, int screenHeight) {
	/* list iterator */
	node_pointer iterator = get_first_element(&s->aliens);
	
	/* update aliens */
	while( iterator != NULL ) {
		
		/* update position through squad speed */
		iterator->o.x += s->x_speed;
		iterator->o.y += s->y_speed;
		/* update position through individual speed */
		iterator->o.x += iterator->o.x_speed;
		iterator->o.y += iterator->o.y_speed;
		
		/* check out of bounds */
		if( x_out_of_bounds(&iterator->o, screenWidth) ) {
			// invert x_speed value
			s->x_speed = - s->x_speed;
		}
		
		if( y_out_of_bounds(&iterator->o, screenHeight) ) {
			// GAME OVER ...
			game_over = TRUE;
		}
		
		/* check collision with bullets */
		if( check_collision_bullets(&iterator->o, bullets, UP) ) {
			/* if alien is rushing down */
			if( iterator->o.y_speed < 0 ){
				s->rushing--;
			}
			explode(&iterator->o);
			iterator = remove_item(iterator, &s->aliens);
			score += KILL_POINTS;
			s->aliensAlive--;
		}
				
		/* tries to shoot! */
		if( will_shoot(s) )
			new_bullet(iterator->o.x  , iterator->o.y + iterator->o.size, DOWN);
			
		/* tries to rush ! */
		if ( will_rush(s) && s->rushing < s->canRush) {
			iterator->o.y_speed = ALIEN_Y_SPEED;
			s->rushing ++;
		}
		
		iterator = iterator->next;
	}
	
	/* check end of wave */
	if ( s->aliensAlive == 0 ) {
		if( s->wave < MAX_WAVES )
			next_wave(s, screenWidth, screenHeight);
		else
			win = TRUE;
		return;
	}
}

/* update every object variables */
void update_objects(int screenWidth, int screenHeight) {
	/* list iterator */
	node_pointer iterator = get_first_element(&bullets);
	
	/* update bullets... */
	/* for each element, update bullet ! */
	while( iterator != NULL ) {
		update_object_position(&iterator->o);
		
		/* check out of bounds */
		if( y_out_of_bounds(&iterator->o, screenHeight) ) {
			/* remove bullet */
			 iterator = remove_item(iterator, &bullets);
		}
		
		iterator = iterator->next;
	}
	
	/* update enemies and player spaceship*/
	update_squad(&enemies, &bullets, screenWidth, screenHeight);
	update_spaceship(&main_spaceship, 0, screenWidth);
	
	/* detect collisions */
	if( check_collision_bullets(&main_spaceship, &bullets, DOWN) || check_collision_bullets(&main_spaceship, &enemies.aliens, DOWN) ) {
		// GAME OVER !
		game_over = TRUE;
	}
}


/* draw all objects */
void draw_objects() {
	/* list iterator */
	node_pointer iterator = get_first_element(&bullets);
	
	/* draw bullets ... */
	/* for each element, draw bullet ! */
	while( iterator != NULL ) {
		draw_bullet(&iterator->o);
		iterator = iterator->next;
	}
	
	/* draw enemy squad */
	draw_squad(&enemies);
	
	/* draw spaceship ...*/
	draw_spaceship(&main_spaceship);
}
