#include <stdio.h>
#include <stdlib.h>
#include "quicksort.h"

void QuickSort(TipoEntidade *e , Indice n){
  Ordena(0 , n-1 , e);
}

void Ordena(Indice esq, Indice dir, TipoEntidade *e){
  Indice i = esq;
  Indice j = dir;
  if(dir <= MINPARTICAO || esq >= (dir-MINPARTICAO)){ //ordena por inserção para um vetor menor que 20
    InsertionSort(esq , dir , e);
  }
  Particao(esq , dir , &i , &j , e);
  if(esq < j) Ordena(esq , j , e);
  if(i < dir) Ordena(i , dir , e);
}

void Particao(Indice esq , Indice dir , Indice *i , Indice *j, TipoEntidade *e){
  TipoEntidade x; //pivo do quicksort
  TipoEntidade aux; //estrutura para a troca
  Indice meio = (*i + *j) / 2 ;
  
  //obtem o pivo como o centro do vetor
  x.pageviews = e[meio].pageviews;
  
  do{
    while(x.pageviews > e[*i].pageviews)(*i)++; //compara os elementos da esquerda com o pivo
    while(x.pageviews < e[*j].pageviews)(*j)-- ;//compara os elementos da direita com o pivo
 
    if(*i <= *j){ //efetua a troca
      aux = e[*i] ;
      e[*i] = e[*j];
      e[*j] = aux;
      (*i)++ , (*j)-- ; //move os apontadores
    }
  }while(*i <= *j);
}

void InsertionSort(Indice esq , Indice dir ,TipoEntidade *e){
  int i, j;
  TipoEntidade aux;
  for(i=esq+1 ; i<=dir ; i++){
    aux = e[i];
    j = i-1;
    while( j >= esq && e[j].pageviews >= aux.pageviews){
      if(e[j].pageviews == aux.pageviews) //se as pageviews são iguais, compara alfabeticamente para fazer a inserção
	if(OrdemAlfabetica(aux , e[j]) > 0) break;
      e[j+1] = e[j];
      j--;
    }
    e[j+1] = aux;
  }
}

int OrdemAlfabetica(TipoEntidade t1 , TipoEntidade t2){
  return strcmp(t1.url , t2.url);
}