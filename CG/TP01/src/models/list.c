#include "list.h"

/* inicia lista encadeada */
void init_list(list *l) {
	l->first = (node_pointer) malloc (sizeof(node));
	l->first->next = NULL;
	l->first->previous = NULL;
	l->numberOfElements = 0;
	l->last = l->first;
}

int is_empty(list *l) {
	return (l->first == l->last);
}

/* insere novo objeto na lista */
void insert(list *l, object obj) {
	
	node_pointer old_last = l->last;
	
	l->last->next = (node_pointer) malloc (sizeof(node));
	l->last = l->last->next;
	l->last->o = obj;
	l->last->next = NULL;
	l->last->previous = old_last;
	l->numberOfElements ++;
}

node_pointer get_first_element(list *l) {
	return l->first->next;
}

node_pointer remove_item(node_pointer p, list *l) {
	node_pointer previous_node = p->previous;
	node_pointer next_node = p->next;
	previous_node->next = next_node;
	if ( next_node != NULL )
		next_node->previous = previous_node;
	else
		l->last = previous_node;
	free(p);
	l->numberOfElements --;
	
	return previous_node;
}

/* remove o ultimo elemento da lista */
void remove_last(list *l) {
	
	node_pointer removed_node = l->last;
	
	l->last = l->last->previous;
	l->last->next = NULL;
	/* desaloca o no da memoria */
	free(removed_node);
	l->numberOfElements--;
}

void clear_list(list *l) {

	node_pointer removed_node = l->first->next;
	node_pointer aux;
	
	while( removed_node != NULL	) {

		aux = removed_node;
		removed_node = removed_node->next;
		free(aux);
	}
	
	l->last = l->first;
	
	l->numberOfElements = 0;
}
