#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <malloc.h>

typedef struct estrutura {
    int chave;
    struct estrutura *esq;
    struct estrutura *dir;
} NO;

// Inicialização da árvore vazia
void inicializarArvore(NO* *raiz) {
    *raiz = NULL;
}

// Inserção de um nó em árvore comum (sem ordem) esq:pos=1 dir:pos=2
bool inserirNo(NO* *raiz, NO* pai, int ch, int pos) {
    NO* novo;
    if(pai) {
        if( ((pos==1) && (pai->esq!=NULL))||
        ((pos==2) && (pai->dir!=NULL))) {
            return(false);
        }
    }
    novo = (NO*) malloc(sizeof(NO));
    novo->chave = ch;
    novo->esq = NULL;
    novo->dir = NULL;
    if(!pai) *raiz = novo;
    else {
        if(pos==1) // esquerda
            pai->esq = novo;
        else
            pai->dir = novo;
    }
}

/*
ATIVIDADE 1

Escrever uma função que, dado um elemento p garantidamente existente em
uma árvore binária, crie um novo filho esquerdo com o valor de chave
correspondente à chave do pai (p) mais a chave do filho direito, se houver. Se já
houver filho esquerdo, nada deve ser executado.
void novoEsquerdo(NO* p)
*/

void novoEsquerdo(NO* p) {
    if (p->esq) return;

    NO* novo = (NO*) malloc(sizeof(NO));
    if (p->dir) {
        novo->chave = p->chave + p->dir->chave;
    }
    else novo->chave = p->chave;

    novo->esq = NULL;
    novo->dir = NULL;
    p->esq = novo;
}


/*
ATIVIDADE 2
(1) Escreva a ordem de visita das chaves da árvore da imagem anexa
(ou ver slides da aula sobre percursos em árvore, ao final), nos
percursos pré-ordem, em ordem, pós ordem e em nível.
Pré-ordem: 18 - 17 - 12 - 3 - 9 - 15 - 2 - 13 - 16 - 6 - 5
Em ordem: 3 - 12 - 9 - 17 - 2 - 15 - 13 - 18 - 6 - 16 - 5
Pós-ordem: 3 - 9 - 12 - 2 - 13 - 15 - 17 - 6 - 5 - 16 - 18
Em nível: 18 - 17 - 16 - 12 - 15 - 6 - 5 - 3 - 9 - 2 - 13



Escreva um algoritmo que, dada uma chave ch garantidamente
existente em uma posição folha (ou seja, 3,9,2,13,6 ou 5 no
exemplo), efetue a sua exclusão.
void excluirFolha(NO* *raiz, int ch)
*/
void excluirFolha(NO* * raiz, int ch) {
    NO* p = *raiz;
    if (p) {
        if (p->esq && p->esq->chave == ch) {
            free(p->esq);
            p->esq = NULL;
        }

        else if (p->dir && p->dir->chave == ch) {
            free(p->dir);
            p->dir = NULL;
        }

        else {
            excluirFolha(&(p->esq), ch);
            excluirFolha(&(p->dir), ch);
        }
    }
}

// Retorna o endereço do pai da chave procurada (usando função void)
void travessiap(NO* p, int ch, NO* *no_pai, bool *achou) {
    if(p) {
        if(p->esq)
            if(p->esq->chave == ch) {
                *achou = true;
                *no_pai = p;
            }
            if(!*achou)
                if(p->dir)
                    if(p->dir->chave == ch) {
                        *achou = true;
                        *no_pai = p;
                    }
            if(!*achou)
                travessiap(p->esq, ch, no_pai, achou);
            if(!*achou)
                travessiap(p->dir, ch, no_pai, achou);
    }
}

int main () {
    NO* raiz = (NO*) malloc(sizeof(NO));
    raiz->chave = 100;
    raiz->esq = NULL;
    raiz->dir = NULL;
    printf("              %d \n",raiz->chave);

    inserirNo(&raiz, raiz, 50, 1);
    inserirNo(&raiz, raiz, 70, 2);
    printf("     %d                     %d \n",raiz->esq->chave,raiz->dir->chave);
    inserirNo(&raiz, raiz->esq, 30, 1);
    inserirNo(&raiz, raiz->esq, 20, 2);
    inserirNo(&raiz, raiz->dir, 10, 1);
    inserirNo(&raiz, raiz->dir, 5, 2);
    printf("%d       %d             ",raiz->esq->esq->chave,raiz->esq->dir->chave);
    printf(" %d     %d \n\n\n",raiz->dir->esq->chave,raiz->dir->dir->chave);

    excluirFolha(&raiz,5);
    if (raiz->dir->dir) printf("ela existe");

    printf("              %d \n",raiz->chave);
    printf("     %d                     %d \n",raiz->esq->chave,raiz->dir->chave);
    printf("%d       %d             ",raiz->esq->esq->chave,raiz->esq->dir->chave);
     printf(" %d",raiz->dir->esq->chave);

    return 0;
}
