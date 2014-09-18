#define TRUE 1
#define FALSE 0
#define BYTE 9
#define MAXBUFFER 60
#include "lista.h"

void primeiraleitura(FILE *fp , TipoLista *l);
int pesquisacaractere(TipoItem *t,int n, unsigned char c);
void ordenaauxiliar(TipoLista *l);
void huffman(TipoLista *l);
void segundaleitura(FILE *fp , TipoLista *l, char *destino);
void escrevetabela(FILE *fw , TipoLista *l);
void tratabuffer(char ** buffer, FILE *fw);
void freeall(TipoLista *l);
void imprimebytes(char *imprime, FILE *fw);
void imprimeresto(char *resto , FILE *fw);
void letabela(FILE *fp , TipoLista *l);
void descomprime(FILE *fp , Ponteiro a, char *destino);
void convertedecimal(int c, char **caminho, int resto);
