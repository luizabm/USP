#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>


#define MAX 50

typedef struct {
    int chave;
} REGISTRO;

typedef struct {
    REGISTRO A[MAX];
    int nroElem;
} LISTA;

// Inicialização
void inicializarLista(LISTA* l) {
    l->nroElem = 0;
}

// Retornar o número de elementos
int tamanho(LISTA* l) {
    return l->nroElem;
}

// Exibição dos elementos na lista
void exibirLista(LISTA* l) {
    int i;
    printf("Lista: \" ");
    for (i=0; i<l->nroElem; i++) {
        printf("%i ", l->A[i].chave);
    }
    printf(" \" \n");
}

// Busca sequencial, retornando a posição do elemento
int buscaSequencial(LISTA* l, int ch) {
    int i = 0;
    while (i < l->nroElem) {
        if (ch == l->A[i].chave) return i;
        else i++;
    }
    return -1;
}

// Inserção de elemento na posição passada por parâmetro
bool inserirElemLista(LISTA* l, REGISTRO reg, int i) {
    int j;
    if ((l->nroElem == MAX) || (i<0) || (i> l->nroElem)) return false;
    for (j = l->nroElem; j>i; j--) {
        l->A[j] = l->A[j-1]; // Deslocados para a direita
    }
    l->A[i] = reg;
    l->nroElem++;
    return true;
}

// Exclusão de um elemento passado por parâmetro
bool excluirElemLista(int ch, LISTA* l) {
    int pos, j;
    pos = buscaSequencial(l,ch);
    if(pos == -1) return false; // Não encontrado
    for (j=pos; j < l->nroElem-1; j++) {
        l->A[j] = l->A[j+1];
    }
    l->nroElem--;
    return true;
}

/*
1. Dada uma lista sequencial l não ordenada que admite repetição de chaves, e um valor
de chave x, retorne o número de vezes que x aparece na lista.
int ocorrencias(LISTA* l, int x)

2. Verifique se duas listas sequenciais l1 e l2 são idênticas (i.e., com as mesmas chaves,
na mesma ordem e com o mesmo tamanho), retornando true/false conforme o caso.
bool identicas(LISTA* l1, LISTA *l2)
*/

int ocorrencias(LISTA* l, int x) {
    int contador = 0;
    if (l->nroElem == 0) return contador;
    int i;
    for (i=0; i < l->nroElem; i++) {
        if (x == l->A[i].chave) contador++;
    }
    return contador;
}

bool identicas(LISTA* l1, LISTA *l2) {
    if (l1->nroElem != l2->nroElem) return false;
    int i;
    for (i=0; i < l1->nroElem; i++) {
        if (l1->A[i].chave != l2->A[i].chave) return false;
    }
    return true;
}


int main() {
    LISTA teste1;
    LISTA teste2;
    LISTA teste3;
    REGISTRO registroTeste;
    inicializarLista(&teste1);
    inicializarLista(&teste2);
    inicializarLista(&teste3);

    for (int i = 0; i<MAX; i++) {
        registroTeste.chave = rand() % 20;
        inserirElemLista(&teste1,registroTeste,i);
        inserirElemLista(&teste2,registroTeste,i);
    }

    for (int i = 0; i<MAX; i++) {
        registroTeste.chave = rand() % 20;
        inserirElemLista(&teste3,registroTeste,i);
    }

    exibirLista(&teste1);
    exibirLista(&teste2);
    exibirLista(&teste3);
    printf("Aparece %d vezes \n",ocorrencias(&teste1,9));

    printf("As listas 1 e 2 são idênticas? %d \n",identicas(&teste1,&teste2));
    printf("As listas 1 e 3 são idênticas? %d \n",identicas(&teste1,&teste3));

    return 0;
}




