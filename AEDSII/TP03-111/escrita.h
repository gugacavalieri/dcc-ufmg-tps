#include "heap.h"

void EscreveRodada(int entidades, int rodada , TipoEntidade *e);
void AbreEscrita(char *arquivo , FILE **fw);
void FechaEscrita(FILE **fw);
void EscreveMaior(FILE *fw , TipoHeap *h);
//void FechaRodadas(int rodadas , TipoHeap *h);