#include "arvore.h"

typedef struct celula * Apontador;

typedef struct celula{
    TipoArvore a;
    Apontador prox;
}TipoCelula;

typedef struct lista{
    Apontador primeiro, ultimo;
    TipoItem *aux; // vetor auxiliar para a leitura
    int tam; //tamanho do vetor auxiliar
    int chars;
}TipoLista;

// FUNÇÕES DA LISTA //
void FazListaVazia(TipoLista *l);
void crialista(TipoLista *l);
void removemenor(TipoLista *l , Ponteiro *n);
void insereordenado(TipoLista *l , Ponteiro t1, Ponteiro t2);
void inserefinal(TipoLista *l, int freq);
void freelista(TipoLista *l);
void inserelista(TipoLista *l , TipoItem t);



