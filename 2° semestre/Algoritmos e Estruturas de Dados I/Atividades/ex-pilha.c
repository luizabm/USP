#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <malloc.h>

typedef struct estrutura {
    int chave;
    struct estrutura *prox;
} NO;

typedef struct {
    NO* inicio;
} LISTA;

typedef struct {
    NO* topo;
} PDINAM;

/* FUNÇÕES DA LISTA LIGADA (AUXILIARES PRO EXERCÍCIO) */
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
    if(p) if(p->chave == ch) return(p);
    return(NULL);
}

// Inserção da chave ch na lista ordenada sem duplicações
bool inserirElemListaOrd(int ch , LISTA* l) {
    NO* novo;
    NO* ant;
    novo = buscaSeqOrd(ch, *l, &ant);
    // if(novo) return(false);
    novo = (NO*) malloc(sizeof(NO));
    novo->chave = ch;

    if(!l->inicio) { // 1a. inserção em lista vazia
        l->inicio = novo;
        novo->prox = NULL;
    }

    else {
        if(!ant) { // inserção no início da lista
            novo->prox = l->inicio;
            l->inicio = novo;
        }

        else { // inserção após um nó existente
            novo->prox = ant->prox;
            ant->prox = novo;
        }
    }
    return(true);
}

/* FUNÇÕES DA PILHA */

// Inicialização da pilha dinâmica
void inicializarPdinam(PDINAM* p) {
    p->topo = NULL;
}

// Quantos elementos existem
int tamanhoPdinam(PDINAM p) {
    NO* p1 = p.topo;
    int tam = 0;
    while(p1) {
        tam++;
        p1 = p1->prox;
    }
    return(tam);
}

void exibirPilha(PDINAM* p) {
    NO* p1 = p->topo;
    while (p1) {
        printf("%d",p1->chave);
        p1 = p1->prox;
    }
}

// Inserir item no topo
void push(int ch, PDINAM* p) {
    NO* novo = (NO*) malloc(sizeof(NO));
    novo->chave = ch;
    novo->prox = p->topo;
    p->topo = novo;
}

// Retirar a chave do topo ou -1
int pop(PDINAM* p) {
    NO* aux;
    int ch;
    if(!p->topo) return(-1);
    aux = p->topo;
    ch = aux->chave;
    p->topo = p->topo->prox;
    free(aux);
    return(ch);
}

// Reinicialização da pilha estática
void reinicializarPilha (PDINAM* p) {
    NO* apagar;
    NO* p1 = p->topo;
    while (p1) {
        apagar = p1;
        p1 = p1->prox;
        free(apagar);
    }
    p->topo = NULL;
}

/*
EXERCÍCIO - PILHAS
Dada uma lista ligada de elementos inteiros *p, escreva um algoritmo que
retorne uma cópia invertida da lista utilizando uma pilha dinâmica como
estrutura auxiliar.
- Dica: use a função PUSH da apostila para empilhar, e depois use POP com a
função de cópia do exercício anterior para obter a lista invertida.
NO* copiaInvertida(NO* p)
*/

NO* copia(NO* p) {
    NO* novaLista = NULL;
    NO* aux = NULL;
    NO* atual = p;

    // Primeiro nó:
    if (atual) {
        novaLista = (NO*) malloc(sizeof(NO));
        novaLista->chave = atual->chave;
        novaLista->prox = NULL;
        atual = atual->prox;
    }

    aux = novaLista;

    // Demais nós:
    while (atual) {
        aux->prox = (NO*) malloc(sizeof(NO));
        aux = aux->prox;
        aux->chave = atual->chave;
        aux->prox = NULL;
        atual = atual->prox;
    }

    return novaLista;
}

NO* copiaInvertida(NO* p) {
    PDINAM* pilha = (PDINAM*) malloc(sizeof(PDINAM));
    pilha->topo = NULL;
    NO* copia = NULL;
    NO* aux = NULL;

    while (p) {
        push(p->chave,pilha);
        p = p->prox;
    }

    if (pilha->topo) { // Primeiro nó
        copia = (NO*) malloc(sizeof(NO));
        copia->chave = pilha->topo->chave;
        copia->prox = NULL;
        pop(pilha);
    }

    aux = copia;

    while (pilha->topo) {
        aux->prox = (NO*) malloc(sizeof(NO));
        aux = aux->prox;
        aux->chave = pilha->topo->chave;
        aux->prox = NULL;
        pop(pilha);
    }

    return copia;
}

int main() {
    // Declaração e inicialização da lista ligada
    LISTA teste1;
    LISTA teste2;
    LISTA teste3;
    inicializarLista(&teste1);
    inicializarLista(&teste2);
    inicializarLista(&teste3);

    // Inserção de elementos na lista 1
    for (int i = 0; i<50; i++) {
        int aux = rand()%50;
        inserirElemListaOrd(aux,&teste1);
    }

    // Inserção de elementos na lista 2
    for (int i = 0; i<20; i++) {
        int aux = rand()%50;
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

    // Teste de copia()
    printf("\n\n Teste do método cópia: \n\n");
    NO* aux = copiaInvertida(teste1.inicio);
    NO* aux2 = copiaInvertida(teste2.inicio);
    NO* aux3 = copiaInvertida(teste3.inicio);

    printf("Lista 1: ");
    while (aux) {
        printf("%d ",aux->chave);
        aux = aux->prox;
    }
    printf("\n\n Lista 2: ");
    while (aux2) {
        printf("%d ",aux2->chave);
        aux2 = aux2->prox;
    }
    printf("\n\n Lista 3: ");
    while (aux3) {
        printf("%d ",aux3->chave);
        aux3 = aux3->prox;
    }

    return 0;
}

