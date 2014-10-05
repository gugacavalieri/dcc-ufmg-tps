#include "squad.h"
#include <time.h>

#define SQUAD_X_SPEED 0.9f
#define SQUAD_Y_SPEED -0.2f

#define NUMBER_ENEMIES 14

#define CHANCE_TO_SHOOT 0.0007f
#define CHANCE_TO_RUSH 0.0007f
#define RAND_LIMIT 1000000

void randomize(void)
{
    srand(time(NULL));
}

void debug_squad(squad *s) {
	
	/* list iterator */
	node_pointer iterator = get_first_element(&s->aliens);
	
	/* draw enemies ...*/
	while( iterator != NULL ){
		debug_alien(&iterator->o, s->x_speed, s->y_speed);
		iterator = iterator->next;
	}
}


/* inicializa as variaveis de um esquadrao */
void init_squad(squad *s, int screenWidth, int screenHeight) {
	
	randomize();
	
	init_list(&s->aliens);
	
	s->numberOfAliens = NUMBER_ENEMIES;
	s->aliensAlive = s->numberOfAliens;
	
	s->x_speed = SQUAD_X_SPEED;
	s->y_speed = SQUAD_Y_SPEED;
	
	/* randomize start direction */
	if( rand() % 10 > 5 )
		s->x_speed = - s->x_speed;
	
	/* inicializa variaveis de proporcao */
	s->enemy_size = (float) screenHeight / ALIEN_SIZE;
	
	s->quarter_screen = (float) screenWidth / 4;
	s->enemy_distance = (float) s->enemy_size * 4;
	
	s->next_enemy_x = (float) s->quarter_screen;
	s->next_enemy_y = (float) (screenHeight - screenHeight / 18);
	
	s->canRush = s->numberOfAliens / 3;
	s->rushing = 0;
	s->numberOfRows = 0;
	
	s->wave = 1;
}

void new_enemy(squad *s, int screenWidth) {
	object enemy;
	init_alien(&enemy, s->next_enemy_x, s->next_enemy_y, s->enemy_size, RED);
	insert(&s->aliens, enemy);
	
	/* update next enemy position */
	s->next_enemy_x += s->enemy_distance;
	
	if( s->next_enemy_x > screenWidth - s->quarter_screen ) {
		/* next row */
		s->next_enemy_y -= s->enemy_distance;
		s->numberOfRows ++;
		s->next_enemy_x = s->quarter_screen - (s->enemy_distance * s->numberOfRows) / 2;
	}
}

/* inicializa lista de inimigos */
void generate_squad(squad *s, int screenWidth) {
	int i;
	for(i = 0 ; i < s->numberOfAliens ; i++) {
		new_enemy(s, screenWidth);
	}
}

void next_wave (squad *s, int screenWidth, int screenHeight) {
	
	s->next_enemy_x = (float) s->quarter_screen;
	s->next_enemy_y = (float) (screenHeight - screenHeight / 18);
	
	s->rushing = 0;
	s->numberOfRows = 0;
	
	s->numberOfAliens *= 2;
	s->canRush = s->numberOfAliens / 3;
	s->aliensAlive = s->numberOfAliens;
	s->y_speed *= 1.1f;
	s->wave ++;
	
	generate_squad(s, screenWidth);
	
}

boolean will_shoot(squad *s) {
	
	int number = random() % RAND_LIMIT;
	
	if( (float) number / RAND_LIMIT > 1.0f - CHANCE_TO_SHOOT )
		return TRUE;
		
	else
		return FALSE;
	
}

boolean will_rush(squad *s) {
	
	int number = random() % RAND_LIMIT;
	
	if( (float) number / RAND_LIMIT > 1.0f - CHANCE_TO_RUSH )
		return TRUE;
		
	else
		return FALSE;
}

void draw_squad(squad *s) {
	
	/* list iterator */
	node_pointer iterator = get_first_element(&s->aliens);
	
	/* draw enemies ...*/
	while( iterator != NULL ){
		draw_alien(&iterator->o);
		iterator = iterator->next;
	}
	
}

void clear_squad(squad *s) {
	clear_list(&s->aliens);
}
