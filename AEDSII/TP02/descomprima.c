#include <stdio.h>
#include <stdlib.h>
#include "procedimentos.h"

int main(int argc, char** argv) {
    //SE OS ARGUMENTOS SÃO NULL'S , RETORNA
    if(argv[1] == NULL || argv[2] == NULL){
    printf("Falta argumentos para a funçao. Retornando.");
    return;
    }

    FILE *fp; //ponteiros de arquivo de escrita
    fp = fopen(argv[1] , "r"); // abre o arquivo para a primeira leitura
    if(fp == NULL) return;
    TipoLista l;
    FazListaVazia(&l); //inicializa a lista
    letabela(fp , &l); //le a tabela para a construção da arvore
    huffman(&l); //recria a árvore
    descomprime(fp , l.ultimo->a.raiz, argv[2]);
    fclose(fp);
    freeall(&l);
}

