#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

void FazListaVazia(TipoLista *l){
    l->primeiro = (Apontador)malloc(sizeof(TipoCelula));
    l->ultimo = l->primeiro;
    l->tam = 0;
    l->chars = 0;
    l->primeiro->prox = NULL;
 
}

void inserelista(TipoLista *l , TipoItem t){
    l->ultimo->prox = (Apontador)malloc(sizeof(TipoItem));
    l->ultimo = l->ultimo->prox;
    l->tam++;
    insereitem(&l->ultimo->a.raiz , t); //insere o item na árvore
}

void crialista(TipoLista *l){
    int i = 0;
    Apontador aux = l->primeiro; // apontador para percorrer a lista
    for(i=0 ; i<l->tam ; i++){
        aux->prox = (Apontador)malloc(sizeof(TipoCelula)); // aloca a prox celula
        aux = aux->prox;
        insereitem(&aux->a.raiz , l->aux[i]); // insere o item na arvore da celula
        aux->a.altura = 1;
        l->ultimo = aux;
    }
}

void removemenor(TipoLista *l , Ponteiro *n){
    Apontador aux; //apontador auxiliar
    aux = l->primeiro->prox; // direciona para o primeiro elemento(menor)
    //guarda o ponteiro da raiz da arvore
    *n = aux->a.raiz;
    l->primeiro->prox = aux->prox; //direciona o apontador
    free(aux);
}

void inserefinal(TipoLista *l, int freq){
    l->ultimo->prox = (Apontador)malloc(sizeof(TipoCelula)); //aloca a nova celula
    l->ultimo = l->ultimo->prox; 
    l->ultimo->prox = NULL;
    l->ultimo->a.raiz = (Ponteiro)malloc(sizeof(TipoNo)); // aloca a raiz
    l->ultimo->a.raiz->t.freq = freq;
}

void freelista(TipoLista *l){
    free(l->aux); //da free no vetor auxiliar
    free(l->primeiro); //da free na cabeça
    free(l->ultimo); //da free na celula alocada para a arvore
}



