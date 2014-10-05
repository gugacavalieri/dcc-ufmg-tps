#include "squad.h"
#include <time.h>

#define SQUAD_X_SPEED 0.9f
#define SQUAD_Y_SPEED -0.2f

#define NUMBER_ENEMIES 14

#define CHANCE_TO_SHOOT 0.0007f
#define CHANCE_TO_RUSH 0.0007f
#define RAND_LIMIT 1000000

/* inicializa semente do rand() */
void randomize(void)
{
    srand(time(NULL));
}

/* debuga variaveis do esquadrao*/
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

/* cria novo inimigo no squad */
void new_enemy(squad *s, int screenWidth) {
	
	/* insere inimigo na lista */
	object enemy;
	init_alien(&enemy, s->next_enemy_x, s->next_enemy_y, s->enemy_size, RED);
	insert(&s->aliens, enemy);
	
	/* update next enemy position */
	s->next_enemy_x += s->enemy_distance;
	
	/* verifica se limite de inimigos na linha foi atingido */
	if( s->next_enemy_x > screenWidth - s->quarter_screen ) {
		/* next row */
		s->next_enemy_y -= s->enemy_distance;
		s->numberOfRows ++;
		s->next_enemy_x = s->quarter_screen - (s->enemy_distance * s->numberOfRows) / 2;
	}
}

/* gera wave de inimigos */
void generate_squad(squad *s, int screenWidth) {
	
	/* para o numero de inimigos da wave, gera inimigos */
	int i;
	for(i = 0 ; i < s->numberOfAliens ; i++) {
		new_enemy(s, screenWidth);
	}
}

/* cria nova wave de inimigos */
void next_wave (squad *s, int screenWidth, int screenHeight) {
	
	/* reseta variaveis de posição dos inimigos */
	s->next_enemy_x = (float) s->quarter_screen;
	s->next_enemy_y = (float) (screenHeight - screenHeight / 18);
	
	/* reseta variaveis do esquadrao */
	s->rushing = 0;
	s->numberOfRows = 0;
	
	s->numberOfAliens *= 2;
	s->canRush = s->numberOfAliens / 3;
	s->aliensAlive = s->numberOfAliens;
	s->y_speed *= 1.1f;
	s->wave ++;
	
	/* gera wave ! */
	generate_squad(s, screenWidth);
	
}

/* calcula a chance de um determinado inimigo do esquadrao s atirar */
boolean will_shoot(squad *s) {
	
	/* calcula uma probabilidade de acordo com as variaveis do esquadrao
	 * e verifica se essa chance é maior do que a necessária
	 * para haver um diparo */
	int number = random() % RAND_LIMIT;
	if( (float) number / RAND_LIMIT > 1.0f - CHANCE_TO_SHOOT )
		return TRUE;
	else
		return FALSE;
}

/* calcula a chance de um determinado inimigo do esquadrao s 
 * iniciar um ataque agressivo */
boolean will_rush(squad *s) {
	
	/* calcula uma probabilidade de acordo com as variaveis do esquadrao
	 * e verifica se essa chance é maior do que a necessária
	 * para haver um ataque agressivo */
	int number = random() % RAND_LIMIT;
	if( (float) number / RAND_LIMIT > 1.0f - CHANCE_TO_RUSH )
		return TRUE;
	else
		return FALSE;
}

/* desenha todos os aliens do esquadrao */
void draw_squad(squad *s) {
	
	/* list iterator */
	node_pointer iterator = get_first_element(&s->aliens);
	
	/* draw enemies ...*/
	while( iterator != NULL ){
		draw_alien(&iterator->o);
		iterator = iterator->next;
	}
	
}

/* desaloca a memoria utilizada pelo squad */
void clear_squad(squad *s) {
	clear_list(&s->aliens);
}
