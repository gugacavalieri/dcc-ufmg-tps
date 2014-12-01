#include <stdlib.h>
#include "ray/RayTracer.h"

/* program parameters */
char *inputFile;
char *outputFile;
int imageWidth, imageHeight;

/* process program argumentos */
int process_arguments(int argc, char **argv) {

	/* check program parameters */
	if (argc < 3) {
		printf("Erro de parametros! Uso:\n");
		printf(
				"./TP03 <ARQUIVO DE ENTRADA> <ARQUIVO DE SAIDA> <LARGURA> <ALTURA>\n");
		return 0;
	}

	/* set input and output paths */
	inputFile = argv[1];
	outputFile = argv[2];

	/* set image output size */
	if (argc == 5) {
		imageWidth = atoi(argv[3]);
		imageHeight = atoi(argv[4]);
	} else {
		imageWidth = DEFAULT_WIDTH;
		imageHeight = DEFAULT_HEIGHT;
	}

	return 1;
}

int main(int argc, char **argv) {

	if (!process_arguments(argc, argv)) {
		return 0;
	}

	RayTracer tracer(imageWidth, imageHeight, outputFile, inputFile);

	/* read scene description */
	if (tracer.readScene() == false) {
		printf("FILE NOT FOUND!\n ABORTING ...\n");
		return 0;
	}

	printf("##### GG RAY_TRACER #####.\n");
	printf("RENDERING SCENE ... PLEASE WAIT.\n");

	clock_t t1, t2;
	t1 = clock();

	/* render scene !*/
	tracer.start();

	t2 = clock();
	int diff = ((int) t2 - (int) t1) / 1000;

	printf("SCENE RENDERED SUCCESSFULLY! PROCESS TOOK: %dms\n", diff);

	return 0;
}
