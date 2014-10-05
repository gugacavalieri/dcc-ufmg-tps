typedef struct struct_squad {
	list aliens;
	float x_speed, y_speed; // squad speed
	
	int attacking;
	
	float next_enemy_x;
	float next_enemy_y;
	float quarter_screen;
	float enemy_distance;
	float enemy_size;
	
	int rushing;
	int canRush;
	int numberOfAliens;
	int aliensAlive;
	int numberOfRows;
	
	int wave;
} squad;
