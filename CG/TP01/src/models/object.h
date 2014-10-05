#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

/* 
 * typedef's
 */
typedef int boolean;

typedef struct struct_object {
	
	float x,y; // postion
	float  x_speed, y_speed; // speed
	float size; 
	int *color;
	
} object;
