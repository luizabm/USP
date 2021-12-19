#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <malloc.h>

typedef struct estrutura {
    int lin;
    int col;
    int info;
    struct estrutura *prox;
} NO;

typedef struct {
    NO* inicio;
    int maxlin;
    int maxcol;
} MATRIZ;

// Inicialização
void inicializarMatriz(MATRIZ* m) {
    m->inicio = NULL;
    m->maxcol = 10;
    m->maxlin = 10;
}

// Busca pela chave ch na lista (ordem crescente) retornando p e ant
NO* buscaSeqOrd(int i, int j, MATRIZ m, NO* *ant) {
    NO* p = m.inicio;
    *ant = NULL;
    while(p) {
        if(p->lin >= i && p->col >= j) break;
        *ant = p;
        p = p->prox;
    }
    if (p && p->lin == i && p->col == j) return p;
    return(NULL);
}

// Inserção da chave ch na lista ordenada sem duplicações
bool inserirElemListaOrd(int ch, int i, int j, MATRIZ* m) {
    NO* novo;
    NO* ant;
    if (ch==0) return;
    novo = buscaSeqOrd(i,j, *m, &ant);
    if(novo) return(false);
    novo = (NO*) malloc(sizeof(NO));
    novo->info = ch;
    novo->lin = i;
    novo->col = j;

    if(!m->inicio) { // 1a. inserção em lista vazia
        m->inicio = novo;
        novo->prox = NULL;
    }

    else {
        if(!ant) { // inserção no início da lista
            novo->prox = m->inicio;
            m->inicio = novo;
        }

        else { // inserção após um nó existente
            novo->prox = ant->prox;
            ant->prox = novo;
        }
    }
    return(true);
}

/*
EXERCÍCIOS
(1) Escrever uma função que retorna o valor da célula [i,j] da matriz
int valor(MATRIZ* m, int i, int j)
(2) Escreva uma função que exiba todos os valores da linha i fornecida, inclusive
zeros.
void exibirLinha(MATRIZ* m, int i)
(3) Escreva um algoritmo para zerar a diagonal principal da matriz.
zerarDiagonal(MATRIZ* m)
*/

int valor(MATRIZ* m, int i, int j) {
    NO* p = m->inicio;
    while (p) {
        if(p->lin >= i && p->col >= j) break;
        p = p->prox;
    }
    if (p && p->lin == i && p->col == j) return p->info;
    return 0; // Não está na matriz
}

void exibirLinha(MATRIZ* m, int i) {
    for (int j = 1; j <= m->maxcol; j++) {
        printf("%d  ", valor(m,i,j));
    }
}

void zerarDiagonal(MATRIZ* m) {
    NO* p = m->inicio;
    NO* ant = NULL;

    // Caso em que o primeiro nó existe:
    if (p && p->lin == p->col) {
        m->inicio = p->prox;
        free(p);
        p = m->inicio;
    }

    while (p) {

        if(p->lin != p->col) {
            ant = p;
            p = p->prox;
        }

        if (!p) return;

        if (p->lin == p->col) {
            ant->prox = p->prox;
            free(p);
            p = ant->prox;
        }
    }
}


/*
void zerarDiagonal (MATRIZ* m) {
    NO* ant = NULL;
    NO* p = m->inicio;
    while (p) {
        if (p->lin == p->col) {
            if (ant) ant->prox = p->prox;
            else m->inicio = p->prox;
            NO* aux = p->prox;
            free(p);
            p = aux;
        }
        else {
            ant = p;
            p = p->prox;
        }
    }
}
*/

int main() {
     // Declaração e inicialização da lista ligada
    MATRIZ teste1;
    MATRIZ teste2;
    MATRIZ teste3;
    inicializarMatriz(&teste1);
    inicializarMatriz(&teste2);
    inicializarMatriz(&teste3);

    // Inserção de elementos na lista 1
    for (int i = 1; i<=teste1.maxlin; i++) {
            for (int j = 1; j<=teste1.maxcol; j++) {
                if (i == j) inserirElemListaOrd(0,i,j,&teste1);
                else inserirElemListaOrd(rand()%50,i,j,&teste1);
            }
    }

    // Inserção de elementos na lista 2
    for (int i = 1; i<=teste2.maxlin; i++) {
            for (int j = 1; j<=teste2.maxcol; j++) {
                int aux = rand()%20;
                inserirElemListaOrd(aux,i,j,&teste2);
            }
    }

    // Inserção de elementos na lista 3
    for (int i = 1; i<=teste3.maxlin; i++) {
            for (int j = 1; j<=teste3.maxcol; j++) {
                int aux = rand()%50;
                inserirElemListaOrd(aux,i,j,&teste3);
            }
    }


    printf("Matriz 1: \n");
    for (int i = 1; i<=teste1.maxlin; i++) {
        exibirLinha(&teste1, i);
        printf("\n");
    }

    printf("\n\n Matriz 2: \n");
    for (int i = 1; i<=teste2.maxlin; i++) {
        exibirLinha(&teste2, i);
        printf("\n");
    }

    printf("\n\n Matriz 3: \n");
    for (int i = 1; i<=teste3.maxlin; i++) {
        exibirLinha(&teste3, i);
        printf("\n");
    }

    zerarDiagonal(&teste1);
    zerarDiagonal(&teste2);
    zerarDiagonal(&teste3);

    printf("\n\n\n APÓS ZERAR A DIAGONAL: \n");
    printf("Matriz 1: \n");
    for (int i = 1; i<=teste1.maxlin; i++) {
        exibirLinha(&teste1, i);
        printf("\n");
    }

    printf("\n Matriz 2: \n");
    for (int i = 1; i<=teste2.maxlin; i++) {
        exibirLinha(&teste2, i);
        printf("\n");
    }

    printf("\n Matriz 3: \n");
    for (int i = 1; i<=teste3.maxlin; i++) {
        exibirLinha(&teste3, i);
        printf("\n");
    }


    return 0;

}
