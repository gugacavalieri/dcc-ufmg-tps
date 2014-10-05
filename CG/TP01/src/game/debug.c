#include <stdio.h>
#include <stdlib.h>


void debug_bullets(list *bullets) {

	/* list iterator */
	node_pointer iterator = get_first_element(bullets);
	
	/* iterate list ...*/
	while( iterator != NULL ){
		debug_bullet(&iterator->o);
		iterator = iterator->next;
	}
	
}

void debug_game() {
	
	printf(" ##### ENTERING DEBUGGING MODE ##### \n");
	printf(" ##### SPACESHIP VARIABLES ##### \n");
	debug_spaceship(&main_spaceship);
	printf(" ##### ALIENS VARIABLES ##### \n");
	debug_squad(&enemies);
	printf(" ##### BULLETS VARIABLES ##### \n");
	debug_bullets(&bullets);
	printf("\n");
}


