#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "escrita.h"

void EscreveRodada(int entidades, int rodada , TipoEntidade *e){
  FILE *fw;
  int i;
  //string para o nome do arquivo
  char *arquivo;
  arquivo = (char*)malloc(ARQUIVO*sizeof(char));
  sprintf(arquivo , "rodada-%d.txt" , (rodada+1)); //imprime o caminho do arquivo na string
  
  fw = fopen(arquivo , "w"); //abre o arquivo
  //imprime o vetor ordenado em ordem decrescente no arquivo
  for(i = entidades - 1 ; i >= 0 ; i--){
    if(strcasecmp(e[i].url , "#") != 0) //se for uma url válida, imprime no arquivo
      fprintf(fw , "%s %d\n" , e[i].url , e[i].pageviews);
  }
  
  free(arquivo);
  fclose(fw);
}

void AbreEscrita(char *arquivo , FILE **fw){
  //abre o arquivo com o "path" e ponteiro recebidos
  *fw = fopen(arquivo , "w");
  
}

void FechaEscrita(FILE **fw){
  //fecha o arquivo de escrita
  fclose(*fw);
}

void EscreveMaior(FILE *fw , TipoHeap *h){
  fprintf(fw , "%s %d\n" , h->e[1].url , h->e[1].pageviews); //imprime a primeira posição do heap no arquivo final
}