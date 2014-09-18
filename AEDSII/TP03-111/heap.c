#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "heap.h"

void ConstroiHeap(int rodadas , TipoHeap *h){
  FILE *fr;
  int i, j;
  //string para o nome do arquivo
  char *arquivo;
  arquivo = (char*)malloc(ARQUIVO*sizeof(char));
  for(i = 1 ; i<=rodadas ; i++){
    sprintf(arquivo , "rodada-%d.txt" , i); //imprime o numero da rodada na string
    h->fo = fopen(arquivo , "r"); //abre o arquivo com o ponteiro 'i'
    fscanf(h->fo , "%s %d\n" , h->e[i].url , &h->e[i].pageviews); //le a url e a pageviews
    if( feof(h->fo) ) remove(arquivo);
    h->arquivos[i] = i; //guarda o numero do arquivo manipulado
    fgetpos(h->fo , &h->pos[i]);
    fclose(h->fo);
  }

  Refaz(1 , rodadas , h); //refaz o heap
  free(arquivo);
  
}

void RefazHeap(Indice esq , Indice dir ,TipoHeap *h){
  Indice i = esq;
  Indice j;
  int aux1;
  TipoEntidade aux;
  fpos_t aux2;
  j = i * 2; //leva j para os filhos de i
  aux = h->e[i];
  aux1 = h->arquivos[i];
  aux2 = h->pos[i];
  while(j <= dir){
    if(j<dir){
      if(h->e[j].pageviews < h->e[j+1].pageviews) j++; //seleciona o maior dos filhos
      else if(h->e[j].pageviews == h->e[j+1].pageviews) //em caso de pageviews iguais, compara a ordem alfabetica dos filhos
	if( OrdemAlfabetica(h->e[j+1] , h->e[j]) < 0) j++;
    }
	
    if(aux.pageviews == h->e[j].pageviews){ //faz a comparacao em Ordem Alfabetica
      if( OrdemAlfabetica(aux , h->e[j]) < 0) break;
    }
    if(aux.pageviews > h->e[j].pageviews) break; //se o pai é maior que o maior filho

    h->e[i] = h->e[j]; //joga o filho para a posição do pai
    h->arquivos[i] = h->arquivos[j];
    h->pos[i] = h->pos[j];
    //POSICIONA OS FILHOS DO NOVO ELEMENTO MOVIDO
    i = j;
    j = i * 2;

  }
  h->e[i] = aux;
  h->arquivos[i] = aux1;
  h->pos[i] = aux2;
}

void Refaz(Indice esq , Indice dir , TipoHeap *h){
  int meio = (esq+dir)/2;
  int i;
  while(meio >= 1){
    RefazHeap(meio,dir,h);
    meio--;
  }
}

void AlocaHeap(int rodadas , TipoHeap *h){
  int i;
  //aloca o vetor de entidades do heap
  h->e = (TipoEntidade*)malloc(rodadas*sizeof(TipoEntidade));
  //aloca o vetor para o manipulamento de arquivos
  h->arquivos = (int*)malloc(rodadas*sizeof(int));
  //aloca o vetor de ponteiros para arquivo
  h->pos = (fpos_t*)malloc(rodadas*sizeof(fpos_t));
  //aloca as strings da estrutura do heap
  for(i=1 ; i<=rodadas ; i++)
    h->e[i].url = (char*)malloc(MAXURL*sizeof(char));
}

int HeapVazio(TipoHeap *h){
 if(h->e[1].pageviews == VAZIO) return TRUE; //se o heap esta vazio, retorna verdadeiro
 else return FALSE; //caso contrario, retorna falso
}

int LeNovoElemento(FILE *fw , TipoHeap *h){
  char *arquivo , *aux;
  arquivo = (char*)malloc(ARQUIVO*sizeof(char));
  sprintf(arquivo , "rodada-%d.txt" , h->arquivos[1]);
  h->fo = fopen(arquivo , "r"); //abre o arquivo
  if(h->fo == NULL){
    h->e[1].pageviews = VAZIO; //escreve a pageviews como vazio
    free(arquivo);
    return 0;
 }
  fsetpos(h->fo , &h->pos[1]); //desloca o ponteiro de leitura

  //caso contrário , lê a proxima entidade do arquivo
  fscanf(h->fo , "%s %d\n" , h->e[1].url , &h->e[1].pageviews);
  
  
  if( feof(h->fo) /*&& strcmp(aux , h->e[1].url) == 0*/){ //verifica o final do arquivo e se a nova url é igual a antiga
    fclose(h->fo); //fecha o arquivo
    remove(arquivo); //remove o arquivo
    free(arquivo);
    return;
  }

  fgetpos(h->fo , &h->pos[1]);
  free(arquivo);
  fclose(h->fo);
  return 0;
}

void FreeHeap(int rodadas , TipoHeap *h){
  int i;
  for(i=1 ; i<=rodadas ; i++) //da free nas strings de urls do heap
      if(h->e[i].url != NULL) free(h->e[i].url);
  free(h->e); //da free no vetor de entidades(Heap)
  free(h->pos); // da free no vetor de ponteiros
  free(h->arquivos);
}
