#include<stdio.h>
#include<stdlib.h>
#include "escrita.h"

int main(int argc, char** argv){
  int entidades , rodada = 0 , esq , i;
  int flag = 1;
  FILE *fp , *fw ; //ponteiro para os arquivos de leitura e escrita
  
  //abre os arquivos de leitura 
  if(AbreLeitura(argv[1] , &fp) == FALSE) return; //retorna se houve erro ao abrir o arquivo
  
  entidades = atoi(argv[3]); //converte o numero de entidades para um inteiro
  //verifica se o numero de entidades é válido
  if(entidades <= 0){
    printf("Numero de entidades inválido\n");
    return;
  }

  if( feof(fp) ){ //se o arquivo está vazio
    printf("Erro! Arquivo vazio! \n");
    return;
  }
  
  AbreEscrita(argv[2] , &fw); //abre o arquivo de escrita
  
  //cria o vetor para a ordenação das entidades
  TipoEntidade e[entidades];
  //aloca as strings do vetor de ordenação
  AlocaUrls(entidades , &e[0]);
  
  do{//executa as rodadas
  LeEntidades(fp , entidades , &e[0]); //le o numero de entidades do arquivo e guarda no vetor
  QuickSort(&e[0] , entidades); // ordena o vetor de acordo com as pageviews
  EscreveRodada(entidades , rodada , &e[0]);
  rodada++;
  }while( !feof(fp) );
  
  TipoHeap h; //cria um heap
  AlocaHeap(rodada+1 , &h); //aloca as urls para inserção no Heap
  ConstroiHeap(rodada , &h);
  
  
  //executa a intercalação dos arquivos
  while( !HeapVazio(&h) ){
    EscreveMaior(fw , &h);
    LeNovoElemento(fw , &h);
    RefazHeap(1 , rodada , &h); //refaz o heap
    flag++;
  }
  
  //fecha os arquivos de leitura e escrita usados
  FechaLeitura(&fp);
  FechaEscrita(&fw);
    
  //da free nos ponteiros usados
  FreeEntidades(entidades , &e[0]);
  FreeHeap(rodada+1 , &h);
}