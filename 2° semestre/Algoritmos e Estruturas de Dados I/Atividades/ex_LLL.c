#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>


#define MAX 50

typedef struct {
    int chave;
    int prox;
} REGISTRO;

typedef struct {
    REGISTRO A[MAX];
    int inicio;
    int dispo;
} LISTA;




// Inicializa��o
void inicializarListaLigadaEstatica(LISTA* l) {
    l->inicio = -1;
    l->dispo = 0;
    for(int i=0; i < (MAX - 1); i++)
        l->A[i].prox = i + 1;
    l->A[MAX - 1].prox = -1;
}

// Exibi��o da lista completa
void exibirLista(LISTA l) {
    int i = l.inicio;
    while (i > -1) {
        printf("%d ", l.A[i].chave);
        i = l.A[i].prox;
    }
}

// Busca sequencial, retornando a posi��o da chave e do anterior
int buscaSeqOrd(int ch, LISTA l, int* ant) {
    int i = l.inicio;
    *ant= -1;
    while (i != -1) {
        if(l.A[i].chave >= ch) break;
        *ant = i;
        i= l.A[i].prox;
    }
    if(i==-1) return -1;
    if(l.A[i].chave==ch) return(i);
    else return -1;
}

// Obter n� dispon�vel - a lista � alterada
int obterNo(LISTA* l) {
    int result = l->dispo;
    if(l->dispo > -1) {
        l->dispo = l->A[l->dispo].prox;
    }
    return(result);
}

// inser��o em lista ordenada sem duplica��es
bool inserirElemListaEncOrd(int ch, LISTA* l) {
    int ant, i;
    i = buscaSeqOrd(ch, *l, &ant);
    if((l->dispo < 0) || (i != -1)) return(false);
    i = obterNo(l);
    l->A[i].chave = ch;
    if(l->inicio<0) {
    // inser��o do primeiro elemento de lista vazia
        l->inicio = i;
        l->A[i].prox = -1;
    }
    else {
        if(ant < 0) {
        // inser��o no in�cio de lista j� existente
            l->A[i].prox = l->inicio;
            l->inicio = i;
        }
        else {
        // inser��o entre dois elementos
            l->A[i].prox = l->A[ant].prox;
            l->A[ant].prox = i;
        }
    }
    return(true);
}

/*
(a) Escreva um algoritmo que troque de lugar a primeira e a �ltima chave da estrutura. Se
a lista possuir menos de dois elementos, n�o h� nada a executar.
void trocar(LISTA* l)

(b) Escreva um algoritmo que copie uma chave em posi��o i para a posi��o seguinte, ou
seja, sobrescrevendo seu sucessor na ordem da lista. Se i j� for a �ltima posi��o da lista,
n�o h� nada a executar.
void sobrescrever(LISTA* l, int i)
*/

void trocar(LISTA* l) {
    int i = l->inicio;
    if (l->inicio == -1 || l->A[i].prox == -1) return;
    int aux = l->A[i].chave;

    while (l->A[i].prox != -1) {
        i = l->A[i].prox;
    }

    l->A[l->inicio].chave = l->A[i].chave;
    l->A[i].chave = aux;
}

void sobrescrever(LISTA* l, int i) {
    if (l->A[i].prox == -1) return;
    int pos = l->A[i].prox;
    l->A[pos].chave = l->A[i].chave;
}

int main() {
    // Declara��o e inicializa��o da lista ligada
    LISTA teste1;
    inicializarListaLigadaEstatica(&teste1);

    // Inser��o de elementos na lista
    for (int i = 0; i<MAX; i++) {
        inserirElemListaEncOrd(i,&teste1);
    }

    // Exibi��o da lista antes da execu��o dos m�todos
    exibirLista(teste1);
    printf("\n \n ");

    // Troca dos elementos de posi��o e exibi��o do resultado
    trocar(&teste1);
    printf("Lista ap�s trocar os elementos de posi��o: \n");
    exibirLista(teste1);
    printf("\n \n");

    // Teste do m�todo de sobrescrever e exibi��o do resultado
    sobrescrever(&teste1,MAX-1);
    sobrescrever(&teste1,0);
    printf("Lista ap�s sobrescrever os elementos: \n");
    exibirLista(teste1);

    return 0;
}
