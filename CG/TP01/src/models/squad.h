typedef struct struct_squad {
	list aliens; // lista de inimigos
	float x_speed, y_speed; // squad speed
	
	int attacking; // numero de inimgos atacando agressivamente
	
	/* varaiveis de posicionamento do squad */
	float next_enemy_x;
	float next_enemy_y;
	float quarter_screen;
	float enemy_distance;
	float enemy_size;
	
	/* variaveis de controle do squad */
	int rushing;
	int canRush;
	int numberOfAliens;
	int aliensAlive;
	int numberOfRows;
	
	/* numero da wave do squad */
	int wave;
} squad;
