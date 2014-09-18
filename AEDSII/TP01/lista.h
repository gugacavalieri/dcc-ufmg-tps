/* 
 * File:   lista.h
 * Author: gustavo
 *
 * Created on 27 de Março de 2011, 14:23
 */

#define MAXJ 100
#define MAO 5
#define JF -1
#define NAIPE 13
#define TRUE 1
#define FALSE 0

typedef struct {
    char *nome;
    int dinheiro, aposta, maiorcarta;
    int mao[MAO], jogada[2], TP[2]; // a mao, a jogada e caso necessario um vetor para guardar a jogada TP, que demanda mais comp.
    int saiu ; //variavel TRUE or FALSE
}TipoJogador;

typedef struct celula * Apontador;

typedef struct celula{
    TipoJogador j;
    Apontador prox;
}TipoCelula;

typedef struct {
    Apontador primeiro, ultimo;
    int pote, apostamax , pingo, numjogadores, cartasinseridas;
    int *repetidas;
}TipoLista;

//////////////////      FUNÇÕES DA LISTA     /////////////////////
void FazListaVazia(TipoLista *l);
void insere(TipoJogador x , TipoLista *l);
Apontador pesquisa(char *nome , TipoLista l);
void freeall(TipoLista *l);

//////////////////      FUNÇÕES DO JOGO     //////////////////////
int lejogador(FILE *fp, int dinicial, TipoLista *l);
int convertemao(FILE *fp , TipoJogador *j , TipoLista *l);
void copiamao(TipoJogador j , Apontador aux);
void pingo(TipoLista *l);
int cartarepetida(int carta ,TipoLista *l);
void verificamao(TipoLista *l);
void verificasaida(TipoLista *l);
void ordenamao(int a[]);
void ordenadinheiro(TipoJogador *j);
void novarodada(TipoLista *l);
int nomecomposto(char *nome);
void determinaganhador(FILE *fw , TipoLista *l);
int cartamaisalta(Apontador aux);
void dividepote(int ganhadores, Apontador *j , TipoLista *l);
void imprimerodada(FILE *fw , int ganhadores, Apontador *j , TipoLista *l);
void imprimeresultado(FILE *fw, TipoLista *l);
void devolvedinheiro(TipoLista *l);

//////////////////      FUNÇÕES DE VERIFICAÇÃO     ///////////////
int RSF(Apontador aux);
int SF(Apontador aux);
int FK(Apontador aux);
int FH(Apontador aux);
int Flush(Apontador aux);
int Straight(Apontador aux);
int TK(Apontador aux);
int TP(Apontador aux);
int OP(Apontador aux);
int VerificaAs(Apontador aux);
