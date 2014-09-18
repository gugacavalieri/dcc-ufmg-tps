#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "leitura.h"

int AbreLeitura(char *arquivo , FILE **fp){
  
  //abre o arquivo com o "path" e ponteiro recebidos
  *fp = fopen(arquivo , "r");
  if(*fp == NULL){
    printf("Erro ao abrir o arquivo");
    return FALSE;
  }
  
}

void FechaLeitura(FILE **fp){
  fclose(*fp);
}

void LeEntidades(FILE *fp , int entidades , TipoEntidade *e){
  int i;
 
  for(i = 0 ; i<entidades ; i++){
    if( feof(fp) ) { //se chegou no final do arquivo
      strcpy(e[i].url , "#"); //url não usada do vetor
      continue;
    }
    
    fscanf(fp , "%s %d\n" , e[i].url , &e[i].pageviews); //le a url e a pageviews do arquivo principal
  }
  
}

void AlocaUrls(int entidades , TipoEntidade *e){
  int i;
  //aloca a url de cada entidade do vetor de ordenação
  for(i=0 ; i<entidades ; i++)
    e[i].url = (char*)malloc(MAXURL*sizeof(char));
}

void FreeEntidades(int entidades , TipoEntidade *e){
  int i;
  //da free nas strings de urls usadas para leitura
  for(i=0 ; i<entidades ; i++)
    free(e[i].url);
}