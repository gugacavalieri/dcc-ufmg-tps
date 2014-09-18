#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"arvore.h"

void insereitem(Ponteiro *a, TipoItem t){
    if( *a == NULL){//cria uma nova arvore já inserindo o elemento
        (*a) = (TipoNo*)malloc(sizeof(TipoNo));
        (*a)->direita = NULL;
        (*a)->esquerda = NULL;
        //copia os itens da estrutura recebida
        (*a)->t.c = t.c; 
        (*a)->t.freq = t.freq;
	(*a)->t.caracteres = NULL;
    }
    else{
        if(t.freq < (*a)->t.freq) insereitem(&(*a)->esquerda , t); //insere para a esquerda
        else insereitem(&(*a)->direita , t); //insere para a direita
    }
}

void inserehuffman(TipoArvore *a, Ponteiro t1, Ponteiro t2){
    
    if(t1->t.caracteres == NULL && t2->t.caracteres == NULL){
        a->raiz->t.caracteres = (char*)malloc(3*sizeof(char));
        strcpy(a->raiz->t.caracteres , "\0");
        //SE É UM CARACTERE IMPRIMÍVEL
        if(t1->t.c >= 32 && t1->t.c <=126){ //A ORDEM NÃO IMPORTA
                a->raiz->t.caracteres[0] = t1->t.c;
                a->raiz->t.caracteres[1] = t2->t.c;
        }
        else{ //A ORDEM IMPORTA
            a->raiz->t.caracteres[0] = t2->t.c;
            a->raiz->t.caracteres[1] = t1->t.c;
        }
    }
    if(t1->t.caracteres != NULL && t2->t.caracteres == NULL){
        int i = strlen(t1->t.caracteres);
        a->raiz->t.caracteres = (char*)malloc((i+2)*sizeof(char));
        strcpy(a->raiz->t.caracteres , "\0");
        sprintf(a->raiz->t.caracteres , "%c" , t2->t.c);
        strcat(a->raiz->t.caracteres , t1->t.caracteres);
    }
    if(t1->t.caracteres == NULL && t2->t.caracteres != NULL){
        int i = strlen(t2->t.caracteres);
        a->raiz->t.caracteres = (char*)malloc((i+2)*sizeof(char));
        strcpy(a->raiz->t.caracteres , "\0");
        sprintf(a->raiz->t.caracteres , "%c" , t1->t.c);
        strcat(a->raiz->t.caracteres , t2->t.caracteres);
    }
    if(t1->t.caracteres != NULL && t2->t.caracteres != NULL){
        a->raiz->t.caracteres = (char*)malloc((strlen(t1->t.caracteres) + strlen(t2->t.caracteres) +1)*sizeof(char));
        strcpy(a->raiz->t.caracteres , "\0");
        strcat(a->raiz->t.caracteres , t1->t.caracteres);
        strcat(a->raiz->t.caracteres , t2->t.caracteres);
    }
        // INSERE A ARVORE DA ESQUERDA //
     a->raiz->esquerda = t1;//copia os nós da esquerda
        // INSERE A ARVORE DA DIREITA //
     a->raiz->direita = t2;//copia o item
}

void escrevearvore(Ponteiro a , unsigned char c, char ** buffer){
while(a != NULL){
if(a->esquerda->t.c == c){
        strcat(*buffer , "0");
        break;
    }
    if(a->direita->t.c == c){
        strcat(*buffer , "1");
        break;
}
    if(a->esquerda->t.caracteres != NULL && strchr(a->esquerda->t.caracteres , c) != NULL){  //se o caractere está na subarvore da esquerda
        strcat(*buffer , "0");
	a = a->esquerda;
        continue;
    }
    if(a->direita->t.caracteres != NULL && strchr(a->direita->t.caracteres , c) != NULL){  //se o caractere está na subarvore da esquerda
        strcat(*buffer , "1");
	a = a->direita;
        continue;
    }
}
}

void learvore(FILE *fw , char **buffer, Ponteiro a){
  Ponteiro aux; //ponteiro para percorrer a arvore
  int i = 0 , j; //contador
  char *copia = (char*)malloc(256*sizeof(char));
  strcpy(copia , *buffer); //cria uma cópia do caminho
  int tam = strlen(copia);
  aux = a; //aponta o auxiliar para a raiz
  
  //PERCORRE O CAMINHO DA ARVORE
  while(i<tam){
    if(copia[i] == '0'){
      aux = aux->esquerda; //segue o caminho da esquerda
      i++;
    }
    else{ //SE O CAMINHO É 1
      aux = aux->direita; //segue o caminho da esquerda
      i++;
    }
    if(aux->esquerda == NULL && aux->direita == NULL){
     //O CARACTERE FOI ACHADO
     fprintf(fw , "%c" , aux->t.c); // imprime o caractere no arquivo
     j = i; //guarda a posição dos bits percorridos
     aux = a; //volta para a raiz
    }
  } 
    //VERIFICA SE HÁ RESTO DE BITS NÃO USADOS NO CAMINHO
  if(j < tam){
    char *resto;
    resto = (char*)malloc(30*sizeof(char));
    sprintf(resto , "\0"); //LIMPA A STRING
    
    //COPIA O RESTO DA STRING
    for(i=0 ; j<tam ; i++){
     resto[i] = copia[j];
     j++;
    }
    resto[i] = '\0';
    // LIMPA O BUFFER E COPIA O RESTO PARA O MESMO
    free(*buffer); 
    *buffer = (char*)malloc(256*sizeof(char)); 
    strcpy(*buffer , resto);
    free(resto);
  }
  
  //SE NÃO HÁ RESTO, LIMPA O BUFFER
  else{
  free(*buffer);
  *buffer = (char*)malloc(256*sizeof(char));
  sprintf(*buffer , "\0"); 
  }
  
  //DESALOCA A MEMORIA USADA:
  free(copia);
}

void freearvore(Ponteiro *a){
    if((*a)->esquerda != NULL)
        freearvore(&(*a)->esquerda); //vai dando free na parte esquerda da arvore
    if((*a)->direita != NULL)
        freearvore(&(*a)->direita); //vai dando free na parte esquerda
    if((*a)->t.caracteres != NULL) 
        free((*a)->t.caracteres); //da free na string
    free(*a); //da free no nó / Folha
}
