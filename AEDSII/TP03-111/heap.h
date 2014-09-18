#include "quicksort.h"

typedef struct Heap{
  TipoEntidade *e;
  int *arquivos;
  fpos_t * pos; //vetor para guardar a posição de leitura de cada arquivo
  FILE* fo;
}TipoHeap;

void ConstroiHeap(int rodadas , TipoHeap *h);
void RefazHeap(Indice esq , Indice dir ,TipoHeap *h);
void Refaz(Indice esq , Indice dir , TipoHeap *h);
void AlocaHeap(int rodadas , TipoHeap *h);
int HeapVazio(TipoHeap *h);
int LeNovoElemento(FILE *fw , TipoHeap *h);
void FreeHeap(int rodadas , TipoHeap *h);