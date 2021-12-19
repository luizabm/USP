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
    NO* cabeca;
} LISTA;

// Inicialização (encadeamento duplo, circular e com nó cabeça)
void inicializarLista(LISTA* l) {
    l->cabeca = (NO*) malloc(sizeof(NO));
    l->cabeca->prox = l->cabeca;
    l->cabeca->ant = l->cabeca;
}

// Último elemento da lista (encadeamento duplo, circular e com nó cabeça)
NO* ultimoElemLista(LISTA l) {
    NO* p = l.cabeca->ant;
    if(p == l.cabeca) return(NULL);
    else return(p);
}

// Posição da chave de busca na lista ordenada
NO* buscaSeqOrd(int ch, LISTA l, NO* *ant) {
    NO* p = l.cabeca->prox;
    *ant = l.cabeca;
    l.cabeca->chave = ch; // usa cabeça como sentinela
    while(p->chave < ch) {
        *ant = p;
        p = p->prox;
    }
    if((p != l.cabeca) && (p->chave == ch) ) return(p);
    else return(NULL);
}


// Inserção ordenada sem duplicações
bool inserirElemListaOrd(int ch, LISTA* l) {
    NO* novo;
    NO* ant;
    novo = buscaSeqOrd(ch, *l, &ant);
    if(novo) return(false);
    novo = (NO*) malloc(sizeof(NO));
    novo->chave = ch;
    novo->prox = ant->prox;
    novo->ant = ant;
    novo->prox->ant = novo;
    ant->prox = novo;
    return(true);
}

// Exibição da lista circular e com nó cabeça
void exibirLista(LISTA l) {
    NO* p = l.cabeca->prox;
    while (p!=l.cabeca) {
        printf("%d ",p->chave); // deve ser int
        p = p->prox;
    }
}


/*
ATIVIDADES
(1) Dada uma lista ligada duplamente ligada *l com nó cabeça e circularidade,
escreva um algoritmo que exiba as chaves existentes em ordem reversa.

NO* exibirInvertida(LISTA* l)

(2) Para a mesma lista, escreva um algoritmo para inserir uma nova chave ch
(que pode ser repetida) antes da posição *atual fornecida, criando um novo nó.

void inserirAntes(LISTA* l, int ch, NO* atual)
*/

NO* exibirInvertida(LISTA* l) {
    NO* p = l->cabeca->ant;
    while (p != l->cabeca) {
        printf("%i ",p->chave);
        p = p->ant;
    }
}

void inserirAntes(LISTA* l, int ch, NO* atual) {
    NO* ant = atual->ant;
    NO* novo = (NO*) malloc(sizeof(NO));
    novo->chave = ch;
    novo->prox = atual;
    novo->ant = ant;
    novo->prox->ant = novo;
    ant->prox = novo;
}


int main() {

    // Declaração e inicialização da lista ligada
    LISTA teste1;
    LISTA teste2;
    LISTA teste3;
    inicializarLista(&teste1);
    inicializarLista(&teste2);
    inicializarLista(&teste3);

    // Inserção de elementos nas listas 1 e 2
    for (int i = 0; i<50; i++) {
        int aux = rand()%50;
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

    // Teste de exibição ao contrário
    printf("Teste de exibirInvertida(): \n");
    printf("Lista 1: ");
    exibirInvertida(&teste1);
    printf("\n \n ");

    printf("Lista 2: ");
    exibirInvertida(&teste2);
    printf("\n \n ");

    printf("Lista 3: ");
    exibirInvertida(&teste3);
    printf("\n \n ");

    // Teste de inserir antes
    printf("Teste de inserirAntes(): \n");
    printf("Lista 1: ");
    inserirAntes(&teste1,50,teste1.cabeca->prox);
    exibirLista(teste1);
    printf("\n \n ");

    printf("Lista 2: ");
    inserirAntes(&teste2,50,teste2.cabeca->ant);
    exibirLista(teste2);
    printf("\n \n ");

    printf("Lista 3: ");
    inserirAntes(&teste2,50,teste3.cabeca->ant);
    exibirLista(teste3);
    printf("\n \n ");

    return 0;
}
