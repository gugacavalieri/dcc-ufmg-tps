typedef struct Item{
    unsigned char c;
    int freq;
    unsigned char *caracteres;
}TipoItem;

typedef struct No * Ponteiro;

typedef struct No{
    TipoItem t;
    Ponteiro esquerda;
    Ponteiro direita;
}TipoNo;

typedef struct arvore{
    Ponteiro raiz;
    int altura;
}TipoArvore;

void novono(Ponteiro *a);
void insereitem(Ponteiro *a, TipoItem t);
void inserehuffman(TipoArvore *a, Ponteiro t1, Ponteiro t2);
void escrevearvore(Ponteiro a , unsigned char c, char ** buffer);
void learvore(FILE *fw , char **buffer, Ponteiro a);
void freearvore(Ponteiro *a);



