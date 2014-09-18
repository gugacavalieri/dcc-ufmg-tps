/* 
 * File:   main.c
 * Author: gustavo
 *
 * Created on 27 de Março de 2011, 14:04
 */

#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

/*
 * 
 */
int main(int argc, char** argv) {
    FILE *fp, *fw;//ponteiros de arquivos de leitura e escrita
    TipoLista l;
    FazListaVazia(&l); //inicializa a lista
    fp = fopen("entrada.txt" , "r");
    fw = fopen("saida.txt" , "w");
    int i=0, rodadas, dinicial;
    fscanf(fp , "%d %d" , &rodadas , &dinicial); // le o numero de jogos e o dinheiro inicial
    for(i=0 ; i<rodadas ; i++){
        novarodada(&l); // inicia uma nova rodada
        if(lejogador(fp , dinicial , &l) == FALSE){//se a rodada é inválida
            devolvedinheiro(&l); // devolve o dinheiro apostado
            fprintf(fw, "0 0 I\n"); //imprime a rodada inválida
            free(l.repetidas); //desaloca o vetor de cartas repetidas para uma nova rodada
            continue;
        }
        pingo(&l); // pinga de todos os jogadores da lista
        verificasaida(&l);
        verificamao(&l); //verifica as jogadas se há mais de um jogador jogando
        determinaganhador(fw ,&l);
        free(l.repetidas) ; //desaloca o vetor de cartas repetidas para uma nova rodada
    }
        imprimeresultado(fw, &l);//imprime o resultado final
	freeall(&l); //Limpa a estrutura de ponteiros utilizados na lista
        fclose(fp); //fecha o arquivo de escrita
        fclose(fw);//fecha o arquivo de leitura
}

