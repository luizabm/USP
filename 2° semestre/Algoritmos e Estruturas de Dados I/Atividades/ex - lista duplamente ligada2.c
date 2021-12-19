#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <malloc.h>

typedef struct estrutura {
    int chave;
    struct estrutura *prox;
    struct estrutura *ant;
} NO;

typedef struct {
    NO* inicio;
} LISTA;

// Inicialização
void inicializarLista(LISTA* l) {
    l->inicio = NULL;
}
// Exibição da lista completa
void exibirLista(LISTA l) {
    NO* p = l.inicio;
    while (p) {
        printf("%d ",p->chave);
        p = p->prox;
    }
}

// Busca pela chave ch na lista (ordem crescente) retornando p e ant
NO* buscaSeqOrd(int ch, LISTA l, NO* *ant) {
    NO* p = l.inicio;
    *ant = NULL;
    while(p) {
        if(p->chave >= ch) break;
        *ant = p;
        p = p->prox;
    }
    if(p && p->chave == ch) return(p);
    return(NULL);
}


// Inserção ordenada sem duplicações
bool inserirElemListaOrd(int ch, LISTA* l) {
    NO* novo;
    novo = (NO*) malloc(sizeof(NO));
    novo->chave = ch;

    if (!l->inicio) {
        l->inicio = novo;
        novo->prox = NULL;
        novo->ant = NULL;
    }


    else {
        novo->prox = l->inicio;
        novo->ant = NULL;
        novo->prox->ant = novo;
    }

    return(true);
}

/*
EXERCÍCIOS
Ex1: Dado um inteiro n > 0, criar uma lista duplamente ligada sem cabeça e
sem circularidade de n elementos numerados de 1..n, retornando o ponteiro
para o seu início.
NO* listaNumerada(int n)

Ex2: Dada uma lista do tipo anterior e um ponteiro p garantidamente válido,
mover o elemento p para o fim da lista. Se p já for o último elemento da lista,
não há nada a fazer.
void moverParaFim(LISTA* l, NO* p)
*/
NO* listaNumerada(int n) {
    if (n <= 0) return NULL;
    NO* lista = NULL;
    NO* p = NULL;
    NO* ant = NULL;

    if (!lista) {
        lista = (NO*) malloc(sizeof(NO));
        lista->chave = 1;
        lista->ant = NULL;
        lista->prox = NULL;
    }

    p = lista;
    ant = lista;

    for (int i = 2; i <= n; i++) {
        p->prox = (NO*) malloc(sizeof(NO));
        ant = p;
        p = p->prox;

        p->chave = i;
        p->ant = ant;

        p->prox = NULL;
    }

    return lista;

}

void moverParaFim(LISTA* l, NO* p) {
    if (p->prox == NULL) return;

    NO* novo = (NO*) malloc(sizeof(NO));
    NO* ant = NULL;

    novo->chave = p->chave;

    if (p->ant != NULL) {
        p->ant->prox = p->prox;
        p->prox->ant = p->ant;
    }
    else l->inicio = p->prox;
    free(p);

    ant = l->inicio;
    while(ant->prox) {
        ant = ant->prox;
    }

    ant->prox = novo;
    novo->prox = NULL;
    novo->ant = ant;
}


int main() {

    NO* lista1 = listaNumerada(10);
    NO* lista2 = listaNumerada(20);
    NO* lista3 = listaNumerada(30);


    printf("Teste da lista numerada: \n\n\n");
    while(lista1) {
        printf("%d ",lista1->chave);
        lista1 = lista1->prox;
    }
    printf("\n\n");

    while(lista2) {
        printf("%d ",lista2->chave);
        lista2 = lista2->prox;
    }
    printf("\n\n");

    while(lista3) {
        printf("%d ",lista3->chave);
        lista3 = lista3->prox;
    }
    printf("\n\n");


    // Declaração e inicialização da lista ligada
    LISTA teste1;
    LISTA teste2;
    LISTA teste3;
    teste1.inicio = NULL;
    teste2.inicio = NULL;
    teste3.inicio = NULL;

    // Inserção de elementos nas listas 1 e 2
    for (int i = 0; i<10; i++) {
        int aux = i;
        inserirElemListaOrd(aux,&teste1);
        inserirElemListaOrd(aux,&teste2);
    }

    // Inserção de elementos na lista 3
    for (int i = 0; i<20; i++) {
        int aux = rand()%50;
        inserirElemListaOrd(aux,&teste3);
    }


    // Exibição das listas antes da execução dos métodos
    printf("Lista 1: ");
    exibirLista(teste1);
    printf("\n \n ");

    printf("Lista 2: ");
    exibirLista(teste2);
    printf("\n \n ");

    printf("Lista 3: ");
    exibirLista(teste3);
    printf("\n \n ");

    printf("exibição ok");
    moverParaFim(&teste1,teste1.inicio);
    moverParaFim(&teste2,teste2.inicio->prox);
    moverParaFim(&teste3,teste3.inicio->prox->prox);

    printf("Lista 1: ");
    exibirLista(teste1);
    printf("\n \n ");

    printf("Lista 2: ");
    exibirLista(teste2);
    printf("\n \n ");

    printf("Lista 3: ");
    exibirLista(teste3);
    printf("\n \n ");

    return 0;
}
