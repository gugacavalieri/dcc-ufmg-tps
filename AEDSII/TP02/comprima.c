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
    FazListaVazia(&l);
    primeiraleitura(fp , &l);
    ordenaauxiliar(&l);
    crialista(&l);
    huffman(&l);
    fclose(fp); //fecha o arquivo
    fp = fopen(argv[1] , "r"); // abre o arquivo para a segunda leitura
    segundaleitura(fp , &l , argv[2]);
    fclose(fp); //fecha o arquivo novamente
    freeall(&l); //da free nas estruturas usadas
}
