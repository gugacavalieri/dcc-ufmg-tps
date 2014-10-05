typedef struct struct_node *node_pointer;

typedef struct struct_node {
	object o;
	node_pointer next;
	node_pointer previous;
} node;

typedef struct struct_list {
	node_pointer first;
	node_pointer last;
	int numberOfElements;
} list;



