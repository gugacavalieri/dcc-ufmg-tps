#include <math.h>

/* calcula a orientacao de tres pontos p1, p2, p3 */
float sign(float x1, float y1, float x2, float y2, float x3, float y3) {
	return (x1 - x3) * (y2 - y3) * (x2 - x3) * (y1 - y3);
}

/* calcula distancia entre dois pontos p1 e p2 */
float distance(float x1, float y1, float x2, float y2) {
	
	/* cria o vetor */
	float vector_x = x2 - x1;
	float vector_y = y2 - y1;
	
	/* calcula a norma e retorna */
	float pow2_x = pow(vector_x, 2);
	float pow2_y = pow(vector_y, 2);
	return sqrt(pow2_x + pow2_y);
}
