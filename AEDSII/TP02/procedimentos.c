#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "procedimentos.h"

void primeiraleitura(FILE *fp , TipoLista *l){
    unsigned char c; // caractere auxiliar
    l->tam = 0;
    while(! feof(fp) ){ //le os caracteres até o final do arquivo
        c = getc(fp);
	if(feof(fp)) break;
        if(pesquisacaractere(l->aux , l->tam , c) == FALSE) { //insere o caractere no vetor auxiliar
            l->aux = (Apontador)realloc(l->aux , (l->tam+1)*sizeof(TipoItem));          
            l->aux[l->tam].c = c;
            l->aux[l->tam].freq = 1;
            l->aux[l->tam].caracteres = NULL;
            l->tam++; //incrementa o tamanho do vetor
        }
    }
}

int pesquisacaractere(TipoItem *t,int n, unsigned char c){
    int i;
    for(i=0 ; i<n ; i++){
        if(t[i].c == c){ //se achar o caractere
            t[i].freq++; //incrementa a frequencia do char
            return TRUE;
        }
    }
    return FALSE;
}

void ordenaauxiliar(TipoLista *l){  //Ordena por ShellSort
    int i , j;
    TipoItem aux1; // auxiliar para a troca
    int gap = 1;
    do {
        gap = 3*gap+1;
    } while(gap < l->tam);
    do {
        gap = gap/3;
        for(i = gap; i < l->tam; i++) {
            aux1 = l->aux[i];
            j = i - gap;
            while (j >= 0 && (aux1.freq < l->aux[j].freq 
                    || (aux1.freq == l->aux[j].freq && aux1.c < l->aux[j].c))) {
                l->aux [j + gap] = l->aux[j];
                j -= gap;
            }
            l->aux [j + gap] = aux1;
        }
    } while ( gap > 1);
}

void huffman(TipoLista *l){
    int i;
    for(i=1 ; i<=l->tam-1 ; i++){
    Ponteiro menor1 , menor2;
    removemenor(l , &menor1); //remove o primeiro menor elemento
    removemenor(l , &menor2); //remove o segundo menor elemento
    insereordenado(l, menor1, menor2);// insere ordenadamente na lista
}
}

void insereordenado(TipoLista *l , Ponteiro t1, Ponteiro t2){
    Apontador aux1, aux = l->primeiro->prox;
    aux1 = l->primeiro;
    int novafreq = t1->t.freq + t2->t.freq;
    while(aux != NULL){
    if(novafreq <= aux->a.raiz->t.freq){
        Apontador novo;
        novo = (Apontador)malloc(sizeof(TipoCelula)); //cria a nova celula
        aux1->prox = novo; //redireciona o apontador anterior
        novo->prox = aux; //redireciona o novo apontador
        novo->a.raiz = (TipoNo*)malloc(sizeof(TipoNo)); //aloca a raiz
        novo->a.raiz->t.freq = novafreq; //nova frequencia da raiz é a soma das frequencias
        inserehuffman(&novo->a , t1 , t2); // executa os passos de huffman
        return;
    }
    aux = aux->prox;
    aux1 = aux1->prox;
    }
    inserefinal(l , novafreq); //insere no final da lista
    inserehuffman(&l->ultimo->a, t1 , t2);
}

void segundaleitura(FILE *fp , TipoLista *l, char *destino){
    unsigned char c; //caractere auxiliar
    char *buffer; //buffer para a escrita
    buffer = (char*)malloc(256*sizeof(char));
    FILE *fw; //ponteiro para o arquivo de escrita
    fw = fopen(destino , "w");
    escrevetabela(fw , l); //escreve no arquivo a tabela dos caracteres e as frequencias
    while(!feof(fp)){
        c = getc(fp); //pega o caractere do arquivo
	if(feof(fp)) break;
        escrevearvore(l->ultimo->a.raiz , c, &buffer);
        if(strlen(buffer) >= 8)
            tratabuffer(&buffer , fw);
    }
    //SE HÁ RESTO NO BUFFER:
    if(strlen(buffer) > 0)
    	imprimeresto(buffer , fw); //imprime o resto dos bits do buffer
    free(buffer);
    fclose(fw); //fecha o arquivo de escrita
}

void escrevetabela(FILE *fw , TipoLista *l){
    int i;
    fprintf(fw , "%d\n", l->tam);
    for(i=0 ; i<l->tam ; i++){
	fprintf(fw , "%c%d\n" , l->aux[i].c , l->aux[i].freq);
    }
}

void freeall(TipoLista *l){
    freearvore(&l->ultimo->a.raiz);
    freelista(l);
}

void tratabuffer(char ** buffer, FILE *fw){
    int i, tam = strlen(*buffer), j=0; //pega o tamanho do buffer
    char *aux , *copia;
    copia = (char*)malloc((tam+1)*sizeof(char));
    aux = (char*)malloc(30*sizeof(char));
    strcpy(copia , *buffer);
    for(i=0 ; i<=tam ; i++){
        if((i%8) == 0 && i>=8){ //pega a cadeia de bytes
            imprimebytes(aux , fw); //IMPRIME O BYTE NO ARQUIVO
            free(aux); //RENOVA O AUXILIAR
            aux = (char*)malloc(30*sizeof(char));
            j = 0; 
            aux[j] = copia[i]; //COPIA O I-ESIMO BIT
            j++;
            continue; //CONTINUA A COPIA
        }
        aux[j] = copia[i];
        j++;
    }
    sprintf(*buffer, "\0"); // limpa o buffer
    strcpy(*buffer , aux); //joga o resto da string no buffer
    free(aux); //limpa o aux
    free(copia);  //limpa a copia do buffer
}

void imprimebytes(char *imprime, FILE *fw){
    int i , j , c = 0 ,tam;
    tam = strlen(imprime);
    // CONVERTE O NUMERO BINÁRIO DA STRING PARA UM INTEIRO //
    for(i=0 ; i<tam ; i++){
        j = tam-1-i; //EXPOENTE DE CONVERSÃO
        if(imprime[i] == '1')
           c += ldexp(2 , j-1);
    }
    fprintf(fw , "%c" , c); // IMPRIME A SEQUENCIA CONVERTIDA COMO CARACTERE
}

void imprimeresto(char *resto , FILE *fw){
    imprimebytes(resto , fw); //IMPRIME O RESTO
}

void letabela(FILE *fp , TipoLista *l){
  unsigned char c;
  TipoItem aux; //auxiliar para leitura
  aux.caracteres = NULL;
  int i, num;
  fscanf(fp , "%d", &num); //guarda o numero de chars da tabela
  getc(fp);
  
  for(i=0 ; i<num ; i++){
      fscanf(fp , "%c%d" ,&c, &aux.freq);
      getc(fp);
      aux.c = c;
      inserelista(l , aux); //insere o elemento na lista e na raiz da árvore
    
  }
} 
 
void descomprime(FILE *fp , Ponteiro a, char *destino){
  int resto = FALSE;
  fpos_t posicao; //variavel para guardar a posição do Stream
  unsigned char c;
  char *buffer , *bits;
  bits = (char*)malloc(BYTE*sizeof(char));
  buffer = (char*)malloc(256*sizeof(char));
  sprintf(buffer , "\0");
  
  //ABRE O ARQUIVO DE ESCRITA:
  FILE *fw;
  fw = fopen(destino , "w");
  while(! feof(fp) ){
    c = getc(fp); //le o caractere
    fgetpos(fp , &posicao);
    getc(fp);

    //se c é o ultimo caractere do arquivo
    if(feof(fp)){
    resto = TRUE;
    convertedecimal(c , &bits, resto); //converte o caracte6re para binário
    strcat(buffer , bits); //joga os bits convertidos para o buffer
    learvore(fw , &buffer , a); //le a arvore a partir do buffer
    break;
}
    convertedecimal(c , &bits, resto); //converte o caracte6re para binário
    strcat(buffer , bits); //joga os bits convertidos para o buffer
    learvore(fw , &buffer , a); //le a arvore a partir do buffer
    fsetpos(fp , &posicao);
  }
  
  //DESALOCA A MEMÓRIA USADA
  free(bits);
  free(buffer);
  
  //FECHA O ARQUIVO DE ESCRITA:
  fclose(fw);
}

void convertedecimal(int c, char **caminho, int resto){
    int i, tam ,divisao = c;
    char *numero = (char*)malloc(BYTE*sizeof(char));
    char *aux = (char*)malloc(BYTE*sizeof(char));
    char *inversa = (char*)malloc(BYTE*sizeof(char));
    sprintf(aux , "\0");
    sprintf(inversa , "\0");
    
    //CONVERTE O NUMERO BINARIO PARA DECIMAL
    while(divisao != 0){
        sprintf(numero , "%d\0" , (divisao % 2));
        strcat(aux , numero);
        divisao /= 2;
    }
    tam = strlen(aux);
    //INVERTE A STRING:
    for(i = 0 ; i< tam ; i++)
        inversa[i] = aux[tam-i-1];
    //LIMPA A STRING AUX
    inversa[i] = '\0';
    sprintf(aux , "\0");
    //CONVERTE O NUMERO PARA UMA STRING DE 8 BITS
	if(resto == FALSE)
        while(i < 8){
          strcat(aux , "0");
          i++;
        }
    strcat(aux , inversa);
    //COPIA O NUMERO CONVERTIDO
    strcpy(*caminho , aux);
    //printf("%s\n", aux);
    free(aux);
    free(numero);
    free(inversa);
}
