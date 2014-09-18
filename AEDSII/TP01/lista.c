
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"


void FazListaVazia(TipoLista *l){
    l->primeiro = (Apontador)malloc(sizeof(TipoCelula));
    l->ultimo = l->primeiro;
    l->primeiro->prox = NULL;
    l->numjogadores=0;
}

void insere(TipoJogador x , TipoLista *l){
    l->ultimo->prox = (Apontador)malloc(sizeof(TipoCelula));
    l->ultimo = l->ultimo->prox;
    l->ultimo->j = x;
    l->ultimo->j.nome = (char*)malloc(MAXJ*sizeof(char));
    strcpy(l->ultimo->j.nome , x.nome) ; // copia o nome para um novo endereço
    l->ultimo->prox = NULL;
}

Apontador pesquisa(char *nome ,TipoLista l){
    Apontador aux; // ponteiro auxiliar
    aux = l.primeiro->prox;
    while(aux != NULL){
        if(strcasecmp(nome , aux->j.nome) == 0 ) return aux; // se o nome do jogador já estiver na lista, retorna o ponteiro
        aux = aux->prox;
    }
    return NULL; //retorna NULL caso o jogador não esteja na lista
}


int lejogador(FILE *fp, int dinicial, TipoLista *l){
    int i=0, jogadores, rodada=TRUE;
    char *nome, *aux;
    nome = (char*)malloc(MAXJ*sizeof(char));
    aux = (char*)malloc(MAXJ*sizeof(char));
    TipoJogador auxs; //Jogador Auxiliar
    auxs.nome = (char*)malloc(MAXJ*sizeof(char));
    fscanf(fp , "%d %d", &jogadores , &l->pingo); // le o numero de jogadores na rodada e o valor do pingo
    l->repetidas = (int*)malloc((MAO*jogadores)*sizeof(int)); //aloca o vetor de cartas repetidas
    Apontador p; //Em caso de pesquisa
    while(i < jogadores){
       fscanf(fp , "%s" , nome); // Lê o nome do jogador
       fscanf(fp , "%s" , aux); // le a prox string
       if(nomecomposto(aux) == TRUE){ // se o nome do jogador é composto:
           strcat(nome , " ");
           strcat(nome, aux);
           p = pesquisa(nome , *l); // pesquisa o jogador na lista, e guarda no ponteiro de pesquisa
           if(p != NULL){//se o jogador está na lista
                fscanf(fp , "%s", aux); // le a aposta
                p->j.aposta = atoi(aux); // guarda a aposta na estrutura do jogador
                p->j.saiu = FALSE;
                if(p->j.aposta > l->apostamax) l->apostamax = p->j.aposta; // verifica se a aposta é a maior
                if(p->j.aposta > p->j.dinheiro) //se a aposta for maior que o dinheiro do jogador
                    rodada = FALSE; //jogada inválida
                p->j.dinheiro -= p->j.aposta; // subtrai o dinheiro do jogador da aposta
                l->pote += p->j.aposta; // soma a aposta ao pote;
                if(convertemao(fp , &auxs , l) == FALSE){ //converte e mao e verifica se ha cartas repetidas
                    rodada = FALSE;
                    p->j.dinheiro += p->j.aposta; //se houver cartas repetidas devolve o dinheiro subtraido da aposta
                }
                copiamao(auxs , p); // copia a mao para a lista
        }
            else{ //se o jogador não está na lista
                 strcpy(auxs.nome , nome); // Copia o nome para a estrutura Auxiliar
                 auxs.dinheiro = dinicial;; // Inicializa o dinheiro da estrutura
                 auxs.saiu = FALSE;
                 fscanf(fp , "%s\n" , aux); // Lê a aposta
                 auxs.aposta = atoi(aux); // guarda a aposta na estrutura do jogador
                 if(auxs.aposta > l->apostamax) l->apostamax = auxs.aposta; // verifica se a aposta é a maior
                 if(auxs.aposta > auxs.dinheiro) //se a aposta for maior que o dinheiro do jogador
                    rodada = FALSE; //jogada inválida
                 auxs.dinheiro -= auxs.aposta; //subtrai a aposta do dinheiro do jogador
                 l->pote += auxs.aposta; // soma a aposta ao pote;
                 if(convertemao(fp , &auxs , l) == FALSE){ //converte e mao e verifica se ha cartas repetidas
                    rodada = FALSE;
                    auxs.dinheiro += auxs.aposta; //se houver cartas repetidas devolve o dinheiro subtraido da aposta
                }
                 insere(auxs , l);
                 l->numjogadores++;
        }
           i++;
           continue;
       }
       // Em caso de nome não composto
        p = pesquisa(nome , *l); // pesquisa o jogador na lista, e guarda no ponteiro de pesquisa
        if(p != NULL){//se o jogador está na lista
                p->j.saiu = FALSE;
                p->j.aposta = atoi(aux); // guarda a aposta na estrutura do jogador
                if(p->j.aposta > l->apostamax) l->apostamax = p->j.aposta; // verifica se a aposta é a maior
                if(p->j.aposta > p->j.dinheiro) //se a aposta for maior que o dinheiro do jogador
                    rodada = FALSE; //jogada inválida
                p->j.dinheiro -= p->j.aposta; // subtrai o dinheiro do jogador da aposta
                l->pote += p->j.aposta; // soma a aposta ao pote;
                if(convertemao(fp , &auxs , l) == FALSE){ //converte e mao e verifica se ha cartas repetidas
                    rodada = FALSE;
                    p->j.dinheiro += p->j.aposta; //se houver cartas repetidas devolve o dinheiro subtraido da aposta
                }
                copiamao(auxs , p);// copia a mao para a lista
        }
            else{ //se o jogador não está na lista
                strcpy(auxs.nome , nome); // Copia o nome para a estrutura Auxiliar
                auxs.dinheiro = dinicial;
                auxs.saiu = FALSE;
                auxs.aposta = atoi(aux); // guarda a aposta na estrutura do jogador
                if(auxs.aposta > l->apostamax) l->apostamax = auxs.aposta; // verifica se a aposta é a maior
                if(auxs.aposta > auxs.dinheiro) //se a aposta for maior que o dinheiro do jogador
                    rodada = FALSE; //jogada inválida
                auxs.dinheiro -= auxs.aposta; //subtrai a aposta do dinheiro do jogador
                l->pote += auxs.aposta; // soma a aposta ao pote;
                if(convertemao(fp , &auxs , l) == FALSE) //converte e mao e verifica se ha cartas repetidas
                    rodada = FALSE;
                insere(auxs , l);
                l->numjogadores++;
        }
            i++;
    }
    free(auxs.nome); //desaloca os ponteiros de strings usados
    free(nome); //..
    free(aux);
    return rodada;
}


int convertemao(FILE *fp , TipoJogador *j , TipoLista *l){
    char * carta;
    carta = (char*)malloc(4*sizeof(char));
    int i=0, rodada = TRUE;
    while(i < MAO){ //converte as 5 cartas restantes
        fscanf(fp , "%s " , carta);// le a proxima carta
        if(strstr(carta , "O") != NULL){ // se o naipe == Ouros
            j->mao[i] = -1 + atoi(carta); // Ouros vai de 0 a 12
            if(cartarepetida(j->mao[i] , l) == TRUE) rodada = FALSE; // se a carta é repetida retorna falso
            i++;
            continue;
        }
        if(strstr(carta , "E") != NULL) {//se o naipe == Espadas
            j->mao[i] = 12 + atoi(carta); // Espadas vai de 13 a 25
            if(cartarepetida(j->mao[i] , l) == TRUE) rodada = FALSE; // se a carta é repetida retorna falso
            i++;
            continue;
    }
        if(strstr(carta , "C") != NULL) {//se o naipe == Copas
            j->mao[i] = 25 + atoi(carta); // Copas vai de 26 a 38
            if(cartarepetida(j->mao[i] , l) == TRUE) rodada = FALSE; // se a carta é repetida retorna falso
            i++;
            continue;
    }
        if(strstr(carta , "P") != NULL) {//se o naipe == Paus
            j->mao[i] = 38 + atoi(carta); // Paus vai de 39 a 51
            if(cartarepetida(j->mao[i] , l) == TRUE) rodada = FALSE; // se a carta é repetida retorna falso
            i++;
            continue;
    }
}
    free(carta); //desaloca o vetor de strings
    return rodada;
}

void copiamao(TipoJogador j , Apontador aux){
    int i;
    for(i=0 ; i<MAO ; i++)
        aux->j.mao[i] = j.mao[i];
}

int cartarepetida(int carta ,TipoLista *l){
    int i=0;
    while(i < l->cartasinseridas){
        if(carta == l->repetidas[i]) return TRUE; // se a carta é repetida retorna True
        i++;
    }
    l->repetidas[i] = carta;
    l->cartasinseridas++;
}

void pingo(TipoLista *l){
    Apontador aux; // ponteiro para pesquisa
    aux = l->primeiro->prox;
    while(aux != NULL){
        aux->j.dinheiro -= l->pingo; // subtrai o pingo do jogador
        l->pote += l->pingo;        //adiciona o pingo ao pote da mesa
        aux = aux->prox;
    }
}

void verificasaida(TipoLista *l){
    Apontador aux; //ponteiro para pesquisa
    aux = l->primeiro->prox;
    while(aux != NULL){
        if(aux->j.aposta < l->apostamax){
            aux->j.saiu = TRUE; // jogador saiu do jogo
            aux = aux->prox;
            continue;
        }
        aux = aux->prox;
    }

}

void verificamao(TipoLista *l){
    Apontador aux; //ponteiro para pesquisa
    int i, maior;
    aux = l->primeiro->prox;
    while(aux != NULL){
        if(aux->j.saiu == TRUE){
            aux->j.jogada[0] = JF; //define a jogada como Jogador Fora(JF)
            aux = aux->prox;
            continue;
        }
        ordenamao(aux->j.mao);
        aux->j.jogada[0] = 1 ; //jogada inicial = High Card
        maior = aux->j.mao[0] % NAIPE;
        for(i=1 ; i<MAO; i++){
        if(maior < aux->j.mao[i] % NAIPE){  //guarda a high card
            aux->j.jogada[1] = aux->j.mao[i] % NAIPE;
            aux->j.maiorcarta = aux->j.mao[i] % NAIPE;
            maior = aux->j.mao[i] % NAIPE;
        }
        }
        if(VerificaAs(aux) == TRUE) aux->j.maiorcarta = 13; // o as conta como a maior carta, no caso 13
        
        if(RSF(aux) == TRUE){// Verifica se o jogador possui Royal Straight Flush
            aux = aux->prox;
            continue;
        }
        if(SF(aux) == TRUE){// Verifica se o jogador possui Straight Flush
            aux = aux->prox;
            continue;
        }
        if(FK(aux) == TRUE){// Verifica se o jogador possui RSF
            aux = aux->prox;
            continue;
        }
        if(FH(aux) == TRUE){ // No Full House já é verificado as jogadas OP e TK. E guardada a maior caso haja apenas uma delas
           aux = aux->prox;
            continue;
        }
        if(Flush(aux) == TRUE){ // verifica o Flush
            aux = aux->prox;
            continue;
        }
        if(Straight(aux) == TRUE){ // verifica o Stright
            aux = aux->prox;
            continue;
        }
        if(TP(aux) == TRUE){ //Verifica TP
            aux = aux->prox;
            continue;
        }
        aux = aux->prox;
    }

}

 void ordenamao(int a[]){
     int i,j; // Ordena a mão do jogador por Inserção
     int aux;
     for (i = 1; i < MAO; i++){
        aux = a[i];
        j = i - 1;
         while ( ( j >= 0 ) && ( aux < a[j]) ){
            a[j+1] = a[j];
            j--;
         }
      a[j+1] = aux;
}
     }

void novarodada(TipoLista *l){
    Apontador aux;
    aux = l->primeiro->prox;
    while(aux != NULL){
        aux->j.aposta = 0;
        aux->j.saiu = JF;
        aux->j.jogada[0] = 0;
        aux = aux->prox;
    }
        l->apostamax = 0; // zera a aposta máxima
        l->pote = 0; //zera o pote
        l->cartasinseridas = 0; //zera o contador de cartas do vetor de cartas repetidas
}

int nomecomposto(char *nome){
    if(nome[0] == '0' || nome[0] == '1' || nome[0] == '2'|| nome[0] == '3' || nome[0] == '4'
            || nome[0] == '5' || nome[0] == '6' || nome[0] == '7' || nome[0] == '8' || nome[0] == '9') return FALSE; //verifica se o primeiro caractere da string [e um numero
    return TRUE;
}

void determinaganhador(FILE *fw , TipoLista *l){
    Apontador aux, ganhador;
    Apontador *j;
    j = (Apontador*)malloc(4*sizeof(Apontador)); //aloca o vetor caso haja mais de um ganhador
    int ganhadores=0;
    aux = l->primeiro->prox;
    ganhador = aux; //suponhamos que a maior jogada seja do primeiro jogador
    aux = aux->prox;
    j[0] = ganhador;
    ganhadores = 1;
    while(aux != NULL){
        if(aux->j.saiu == TRUE){ // se o jogador saiu do jogo , continua
            aux = aux->prox;
            continue;
        }
        if(aux->j.jogada[0] > ganhador->j.jogada[0]){ //se a jogada do aux é maior , guarda o aux
            ganhador = aux;
            j[0] = ganhador;
            ganhadores = 1;
            aux = aux->prox;
            continue;
        }
        if(aux->j.jogada[0] == ganhador->j.jogada[0]){ //se a jogada de ambos é igual
            if(aux->j.jogada[0] == 3){ //analisa se a jogada é TP, que é uma jogada que demanda mais comparações
                if(aux->j.TP[0] > ganhador->j.TP[0]){ //compara os pares maiores 
                    ganhador = aux;
                    j[0] = ganhador;
                    ganhadores = 1;
                    aux = aux->prox;
                    continue;
                }
                if(aux->j.TP[0] == ganhador->j.TP[0]){ //se os maiores pares são iguais
                    if(aux->j.TP[1] > ganhador->j.TP[1]){ // compara os pares menores
                        ganhador = aux;
                        j[0] = ganhador;
                        ganhadores = 1;
                        aux = aux->prox;
                        continue;
                    }
                    if(aux->j.TP[1] == ganhador->j.TP[1]){ //se os menores pares são iguais
                        if(aux->j.maiorcarta > aux->j.maiorcarta){//compara a maior carta da mão
                            ganhador = aux;
                            j[0] = ganhador;
                            ganhadores = 1;
                            aux = aux->prox;
                            continue;
                        }
                    }
                }
            }
        if(aux->j.jogada[1] > ganhador->j.jogada[1]){ //se um criterio da jogada é maior, temos um novo ganhador
               ganhador = aux;
               j[0] = ganhador;
               ganhadores = 1;
               aux = aux->prox;
               continue;
        }
        if(aux->j.jogada[1] == ganhador->j.jogada[1]){//se o criterio de desempate da jogada é igual:
            if(cartamaisalta(aux) == TRUE)
                if(aux->j.maiorcarta > ganhador->j.maiorcarta){
                    ganhador = aux;
                     j[0] = ganhador;
                     ganhadores = 1;
                    aux = aux->prox;
                    continue;
    }
            //se não, há empate na rodada
            j[ganhadores] = aux;
            ganhadores++; 
            aux = aux->prox;
            continue;
            
        }
        }
        aux = aux->prox;
}
    dividepote(ganhadores , j , l); //divide o pote entre o numero de ganhadores
    imprimerodada(fw , ganhadores , j , l); // imprime o resultado da rodada
    free(j); // desaloca o vetor auxiliar 
}

int cartamaisalta(Apontador aux){
    if(aux->j.jogada[0] == 8 || aux->j.jogada[0] == 7 || aux->j.jogada[0] == 6 || aux->j.jogada[0] == 5 ||
            aux->j.jogada[0] == 4 || aux->j.jogada[0] == 2 || aux->j.jogada[0] == 1){ //verifica se a jogada possui carta mais alta como desempate
        return TRUE;
    }
}

void imprimerodada(FILE *fw , int ganhadores, Apontador *j , TipoLista *l){
    int i;
    fprintf(fw, "%d %d " , ganhadores , l->pote/ganhadores); //imprime o numero de ganhadores e o montante ganho
        if(j[0]->j.jogada[0] == 10) fprintf(fw, "RSF\n"); // imprime o nome da jogada de acordo com o numero
        if(j[0]->j.jogada[0] == 9) fprintf(fw, "SF\n");
        if(j[0]->j.jogada[0] == 8) fprintf(fw, "FK\n");
        if(j[0]->j.jogada[0] == 7) fprintf(fw, "FH\n");
        if(j[0]->j.jogada[0] == 6) fprintf(fw ,"F\n");
        if(j[0]->j.jogada[0] == 5) fprintf(fw, "S\n");
        if(j[0]->j.jogada[0] == 4) fprintf(fw, "TK\n");
        if(j[0]->j.jogada[0] == 3) fprintf(fw, "TP\n");
        if(j[0]->j.jogada[0] == 2) fprintf(fw, "OP\n");
        if(j[0]->j.jogada[0] == 1) fprintf(fw, "HC\n");
    for(i=0 ; i<ganhadores ; i++){
        fprintf(fw, "%s\n" , j[i]->j.nome); // imprime o nome(s) do(s) ganhador(es)
    }
}

void imprimeresultado(FILE *fw, TipoLista *l){
    Apontador aux; // apontador de pesquisa
    aux = l->primeiro->prox;
    TipoJogador p[l->numjogadores]; // Vetor para ordenação do dinheiro
    int i=0;
    fprintf(fw , "####\n");
    while(aux != NULL){ // Percorre a lista
        p[i] = aux->j; // guarda o jogador no vetor para ordenação
        aux = aux->prox;
        i++;
    }
    ordenadinheiro(p); // ordena o Vetor de acordo com o dinheiro de cada jogador
    for(i=0 ; i<l->numjogadores ; i++){
        fprintf(fw , "%s %d\n",p[i].nome , p[i].dinheiro); //imprime o nome e o dinheiro de cada jogador do vetor
    }
}

void dividepote(int ganhadores, Apontador *j , TipoLista *l){
    int i;
    for(i=0 ; i<ganhadores ; i++)
        j[i]->j.dinheiro += l->pote/ganhadores; //divide o pote entre o(s) ganhador(es)
}

void ordenadinheiro(TipoJogador p[]){
     int i,j;
     int aux;
     TipoJogador x; // Estrutura para a troca
     for (i = 1; i < MAO; i++){ // Ordena por Inserção
        aux = p[i].dinheiro;
        x = p[i];
        j = i - 1;
         while ( ( j >= 0 ) && ( aux > p[j].dinheiro) ){
            p[j+1] = p[j];
            j--;
         }
      p[j+1] = x;
}
}

int RSF(Apontador aux){
    if(aux->j.mao[0] % NAIPE != 0) return FALSE; // se a ultima carta do vetor não é o As retorna 0
    if(aux->j.mao[0] == 0 && aux->j.mao[4] == 12){// verifica o RSF no naipe de Ouros
        aux->j.jogada[0] = 10; //guarda a jogada
        aux->j.jogada[1] = 1; 
        return 1;
    }
    if(aux->j.mao[0] == 13 && aux->j.mao[4] == 25){// verifica o RSF no naipe de Espadas
        aux->j.jogada[0] = 10;//guarda a jogada
        aux->j.jogada[1] = 1;
        return 1;
    }
    if(aux->j.mao[0] == 26 && aux->j.mao[4] == 38){// verifica o RSF no naipe de Copas
        aux->j.jogada[0] = 10;//guarda a jogada
        aux->j.jogada[1] = 1;
        return 1;
    }
    if(aux->j.mao[0] == 39 && aux->j.mao[4] == 51){// verifica o RSF no naipe de Paus
        aux->j.jogada[0] = 10;//guarda a jogada
        aux->j.jogada[1] = 1;
        return TRUE;
    }
    return FALSE;
}

int SF(Apontador aux){
    if(aux->j.mao[1] == aux->j.mao[0] +1){ //a segunda carta é igual a primeira +1
        if(aux->j.mao[2] == aux->j.mao[1] +1)//a terceira carta é igual a segunda +1
            if(aux->j.mao[3] == aux->j.mao[2] +1) // ...
                if(aux->j.mao[4] == aux->j.mao[3] +1){ //..
                      aux->j.jogada[0] = 9; // guarda a jogada
                      aux->j.jogada[1] = aux->j.mao[4] % (NAIPE); // guarda a carta mais alta
                      return TRUE;
                }
    }
    return FALSE;
}

int FK(Apontador aux){
    int i,j, iguais=1;
    for(i=0 ; i<MAO ; i++){//varia as cartas
        if(iguais == 4){ //se o numero de cartas iguais do mesmo naipe é igual a 4, valida a jogada
            aux->j.jogada[0] = 8; // guarda a jogada
            aux->j.jogada[1] = aux->j.mao[i-1] % (NAIPE); // guarda a maior carta do FK
            return TRUE;
        }
        iguais = 1;
        for(j=i+1 ; j<MAO ; j++)
        if(aux->j.mao[i] % (NAIPE) == aux->j.mao[j] % (NAIPE)) iguais++; // compara a primeira carta da mao com os naipes das demais
    }
    return FALSE;
}

int FH(Apontador aux){
    int op;
    if(OP(aux) == TRUE) op = TRUE;//se o jogador possui Trinca e Um Par , valida o Full House
        int temp;
        temp = aux->j.jogada[1]; 
        if(TK(aux) == TRUE && op == TRUE){
        aux->j.jogada[0] = 7 ; //guarda a jogada
        aux->j.mao[4] = temp ; //guarda o valor do Par
        return TRUE;
        }
      return FALSE;
    }

int Flush(Apontador aux){
    if(aux->j.mao[0] >= 0) //se a primeira carta é de Ouros
        if(aux->j.mao[4] <= 12){ //se a ultima carta é de Ouros
            aux->j.jogada[0] = 6;//guarda a jogada
            aux->j.jogada[1] = aux->j.mao[4] % (NAIPE);//guarda a carta mais alta
            return TRUE;
        }

    if(aux->j.mao[0] >= 13)//se a primeira carta é de Espadas
        if(aux->j.mao[4] <= 25){//se a ultima carta é de Espadas
            aux->j.jogada[0] = 6;//guarda a jogada
            aux->j.jogada[1] = aux->j.mao[4] % (NAIPE);//guarda a carta mais alta
            return TRUE;
        }

    if(aux->j.mao[0] >= 26)//se a primeira carta é de Copas
        if(aux->j.mao[4] <= 38){//se a ultima carta é de Copas
            aux->j.jogada[0] = 6;//guarda a jogada
            aux->j.jogada[1] = aux->j.mao[4] % NAIPE;//guarda a carta mais alta
            return TRUE;
        }

    if(aux->j.mao[0] >= 39)//se a primeira carta é de Paus
        if(aux->j.mao[4] <= 51){//se a ultima carta é de Paus
            aux->j.jogada[0] = 6; //guarda a jogada
            aux->j.jogada[1] = aux->j.mao[4] % (NAIPE); //guarda a carta mais alta
            return TRUE;
        }
    return FALSE;
}

int Straight(Apontador aux){
    int i, num[MAO];
    for(i=0 ; i<MAO ; i++){
	if(aux->j.mao[i] % NAIPE == 0){ //se a carta é um Ás, 
		num[i] = 13; //guarda a carta como 13
		continue;
	}
        num[i] = aux->j.mao[i] % (NAIPE); //pega apenas os numeros das cartas e guarda em um vetor aux
}
    ordenamao(num); // ordena o vetor com os numeros das cartas
    if(num[1] == num[0]+1) //se a segunda é a primeira +1
        if(num[2] == num[1]+1)//se a terceira é a segunda +1
            if(num[3] == num[2]+1) //...
                if(num[4] == num[3]+1) {
                    aux->j.jogada[0] = 5;//valida a jogada
                    aux->j.jogada[1] = num[4]; //guarda a maior carta da sequencia
                    return TRUE;
                }
    return FALSE;
    }
    
int TK(Apontador aux){
    int i,j, iguais=1, repetida;
    for(i=0 ; i<MAO ; i++){//varia as cartas
        if(repetida == aux->j.mao[i] % NAIPE) continue;
        if(iguais == 3){ //se o numero de cartas iguais do mesmo naipe é igual a 3, valida a jogada
            aux->j.jogada[0] = 4; // guarda a jogada
            aux->j.jogada[1] = aux->j.mao[i-1] % (NAIPE); // guarda a maior carta do TK
            return TRUE;
        }
        iguais = 1;
        for(j=i+1 ; j<MAO ; j++)
        if(aux->j.mao[i] % (NAIPE) == aux->j.mao[j] % (NAIPE)){ // compara a primeira carta da mao com os naipes das demais
             iguais++;
             repetida = aux->j.mao[i] % NAIPE;
        }
    }
    return FALSE;
}

int TP(Apontador aux){
    int i,j,iguais = 1, pares = 0, troca, repetida;
    for(i=0 ; i<MAO-1 ; i++){ // varia até a quarta carta
        if(iguais == 2) pares++;
        iguais = 1;
         if(repetida == aux->j.mao[i] % NAIPE) continue;
        for(j=i+1 ; j<MAO ; j++)
            if(aux->j.mao[i] % (NAIPE) == aux->j.mao[j] % (NAIPE)){//compara a o numero da carta com o numero da proxima carta
                repetida = aux->j.mao[i] % NAIPE;
                iguais++;
                if(pares == 1){
                     if(aux->j.mao[i] % (NAIPE) > aux->j.TP[0] % (NAIPE)){ // se o novo par é maior que o anterior faz a troca
                        troca = aux->j.TP[0];
                        aux->j.TP[0] = aux->j.mao[i] % (NAIPE) ; //guarda o novo maior par
                         aux->j.TP[1] = troca;
                         continue;
                     }
                     aux->j.TP[1] = aux->j.mao[i] % (NAIPE) ; //guarda o par no menor par
                }
                aux->j.TP[0] = aux->j.mao[i] % (NAIPE);
           }
}
    if(pares == 2){
        aux->j.jogada[0] = 3 ; //guarda a jogada
        return TRUE;
    }
    return FALSE;
}

int OP(Apontador aux){
    int i,j, iguais=1, repetida;
    for(i=0 ; i<MAO ; i++){//varia as cartas
        if(repetida == aux->j.mao[i] % NAIPE) continue;
        if(iguais == 2){ //se o numero de cartas iguais do mesmo naipe é igual a 2, valida a jogada
            aux->j.jogada[0] = 2; // guarda a jogada
            aux->j.jogada[1] = aux->j.mao[i-1] % (NAIPE); // guarda a maior carta do OP
            return TRUE;
        }
        iguais = 1;
        for(j=i+1 ; j<MAO ; j++)
        if(aux->j.mao[i] % (NAIPE) == aux->j.mao[j] % (NAIPE)){// compara a primeira carta da mao com os naipes das demais
             iguais++;
             repetida = aux->j.mao[i] % NAIPE;
        }
    }
    return FALSE;
}

int VerificaAs(Apontador aux){
    int i;
    for(i=0 ; i < MAO ; i++)
        if(aux->j.mao[i] % NAIPE == 0)
            return TRUE ; //se o jogador possui algum Ás, retorna TRUE
    return FALSE;
}

void devolvedinheiro(TipoLista *l){
    Apontador aux; // apontador de pesquisa
    aux = l->primeiro->prox;
    while(aux != NULL){
        if(aux->j.saiu == FALSE){//se o jogador apostou
            aux->j.dinheiro += aux->j.aposta; //recebe o dinheiro da aposta de volta
        }
        aux = aux->prox;
    }
}

void freeall(TipoLista *l){
    Apontador aux, aux1;
    aux = l->primeiro;
    aux1 = aux;
    while(aux != NULL){
	free(aux->j.nome); //limpa os ponteiros alocados para os nomes dos jogadores
        aux = aux->prox;
        free(aux1); // desaloca a celula usada na lista
        aux1 = aux;
}
}
