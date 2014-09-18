#include "leitura.h"

typedef int Indice;

void QuickSort(TipoEntidade *e , Indice n);
void Ordena(Indice esq, Indice dir, TipoEntidade *e);
void Particao(Indice esq , Indice dir , Indice *i , Indice *j, TipoEntidade *e);
void InsertionSort(Indice esq , Indice dir ,TipoEntidade *e);
int OrdemAlfabetica(TipoEntidade t1 , TipoEntidade t2);
