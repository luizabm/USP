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

// Busca binária não recursiva devolvendo o nó pai
NO* buscaNo(NO* raiz, int ch, NO* *pai) {
    NO* atual = raiz;
    *pai = NULL;
    while (atual) {
        if(atual->chave == ch) return(atual);
        *pai = atual;
        if(ch < atual->chave) atual = atual->esq;
        else atual = atual->dir;
    }
    return(NULL);
}

// Inserção em ABB
bool inserir(NO* *raiz, int ch) {
    NO* pai;
    NO* atual = buscaNo(*raiz, ch, &pai);
    if(atual) return false;
    NO* novo = (NO*) malloc(sizeof(NO));
    novo->chave = ch;
    novo->esq = NULL;
    novo->dir = NULL;

    if(!pai) {
        *raiz = novo;
        return(true);
    }

    if(pai->chave > ch) pai->esq = novo;
    else pai->dir = novo;
    return(true);
}

void horiz(NO* p, int d) {
    int i;
    if (p) {
        horiz(p->dir, d+1);
        for (i=1; i<=d; i++) printf("     ");
        printf("%d\n",p->chave);
        horiz(p->esq, d+1);
    }
}


void preOrdem(NO* p) {
    if(p) {
        printf("%d ",p->chave);
        preOrdem(p->esq);
        preOrdem(p->dir);
    }
}

/*
ATIVIDADE
1. Escreva um algoritmo que, dado um nó p em árvore binária, retorne a sua
altura.
int altura(NO* p)

2. Dada uma árvore comum (não ordenada) contendo apenas chaves entre 0 e
100 sem repetição, escreva um algoritmo que retorne a menor chave da estrutura.
Se a árvore esteja vazia, retorne um valor fora do intervalo válido.

*/

int altura(NO* p) {
    if (p) {
        int esq = altura(p->esq);
        int dir = altura(p->dir);
        if (esq > dir) return (esq + 1);
        else return (dir + 1);
    }
}

int menorChave(NO* p) {
    if (!p) return 150;

    int menor = p->chave;
    if (p->esq) {
        int menorEsq = menorChave(p->esq);
        if (menorEsq < menor) menor = menorEsq;
    }

    if (p->dir) {
        int menorDir = menorChave(p->dir);
        if (menorDir < menor) menor = menorDir;
    }

    return menor;
}

/*
ATIVIDADE 2
1. Exibir todas as folhas de uma árvore, em qualquer ordem.

void exibirFolhas(NO* p)

2. Em ABB, exibir os ancestrais de uma chave x, do seu pai até a raiz.

void exibeAncestrais(NO* p, int x)

*/

void exibirFolhas(NO* p) {
    if(p) {
        if (!p->esq && !p->dir)
            printf("%d ",p->chave);
        exibirFolhas(p->esq);
        exibirFolhas(p->dir);
    }
}

void exibeAncestrais(NO* p, int x, bool* encontrou) {
    if (p) {
        *encontrou = false;

        if (p->chave == x) {
            *encontrou = true;
            return;
        }

        if (p->chave > x) {
            exibeAncestrais(p->esq,x,encontrou);
            if (*encontrou) printf("%d ",p->chave);
        }
        else {
            exibeAncestrais(p->dir,x,encontrou);
            if (*encontrou) printf("%d ",p->chave);
        }
    }
}

/*
ATIVIDADE 3
Dada uma chave ch garantidamente existente em uma ABB comum, exiba a
chave precedente a ch na sequência de chaves da estrutura, ou seja, o valor de
chave mais próximo possível de ch, porém inferior a ch.

void precedente(NO* p, TIPOCHAVE ch, ...
*/



void precedente (NO* p, int ch, NO** pai, NO** ancestral) {
    if (p) {
        if (p->chave == ch) {
            // Nó folha
            if (!(p->esq) && !(p->dir)) {
                if ((*pai)->dir && (*pai)->dir == p) printf("%d ",(*pai)->chave);
                if ((*pai)->esq && (*pai)->esq == p && *ancestral) printf("%d ",(*ancestral)->chave);
            }

            // Possui o filho esquerdo
            if (p->esq) {
                NO* aux = p->esq;
                while (aux->dir) aux = aux->dir;
                printf("%d ",aux->chave);
            }

            // Possui apenas o filho direito
            if (p->dir && !(p->esq)) {
                if ((*pai)->dir && (*pai)->dir == p) printf("%d ",(*pai)->chave);
                if ((*pai)->esq && (*pai)->esq == p && *ancestral) printf("%d ",(*ancestral)->chave);
            }

        }

        // Armazena o pai
        *pai = p;

        // Armazena um ancestral (para o caso de o nó estar à esquerda do pai)
        if (p->dir && p->esq && p->esq->chave != ch) *ancestral = p;

        // Chamadas recursivas
        if (p->chave > ch) precedente(p->esq,ch,pai,ancestral);
        else precedente (p->dir,ch,pai,ancestral);

    }
}

/*
void precedente (NO* raiz, NO* p, int ch, NO** aux) {
    if (p) {
        if (p->chave == ch) {
            if (p->esq) printf("%d ", p->esq->chave);
            if (!p->esq && !p->dir) {
                if ((*aux)->esq == p) printf("%d ", raiz->chave);
                if ((*aux)->dir == p) printf("%d ", (*aux)->chave);
            }
        }

        *aux = p;


        if (p->chave > ch) {
            precedente(raiz, p->esq, ch, aux);
        }

        if (p->chave < ch) {
            precedente(raiz, p->dir, ch, aux);
        }
    }
}
*/

/*
void precedente (NO* p, int ch, NO** pai) {
    *pai = NULL;

    while (p) {
        if (p->chave == ch) {
            if (p->esq) printf("%d ",p->esq->chave);
            if (!p->esq && !p->dir) {
                if ((*pai)->esq == p)
                if ((*pai)->dir == p) printf("%d ", (*pai)->chave);
            }
        }

        *pai = p;

        if (p->chave > ch) p = p->esq;
        else p = p->dir;
    }
}

*/


int main() {

    NO* raiz = NULL;

    int contador = 0;
    while (contador < 20) {
        int aux = rand()%20;
        bool insercao = inserir(&raiz,aux);
        if (insercao == true) contador++;
    }

    NO* raiz2 = NULL;
    inserir(&raiz2,10);
    inserir(&raiz2,20);
    inserir(&raiz2,5);

    NO* p = raiz;
    NO* p2 = raiz2;
    NO* p3 = NULL;
    printf("\nSEMANA 1: ");
    printf("\nImpressão das árvores: ");
    horiz(p,1);
    printf("\n\n");
    horiz(p2,1);

    printf("\nTeste da altura: ");
    printf(" \n\n %d ",altura(p));
    printf(" \n\n %d ",altura(p2));

    printf("\nTeste da menor chave: ");
    printf(" \n\n %d ",menorChave(p));
    printf(" \n\n %d ",menorChave(p2));
    printf(" \n\n %d ",menorChave(p3));

    printf("\n\n\n SEMANA 2: ");
    printf("\nTeste da exibição das folhas: ");
    exibirFolhas(p);
    printf("\n\n");
    exibirFolhas(p2);
    printf("\n\n");
    exibirFolhas(p3);

     printf("\n\nTeste da exibição dos ancestrais: ");
    bool encontrou = false;
    exibeAncestrais(p,17,&encontrou);
    printf("\n\n");
    bool encontrou2 = false;
    exibeAncestrais(p2,20,&encontrou2);
    printf("\n\n");
    bool encontrou3 = false;
    exibeAncestrais(p3,10,&encontrou3);
    printf("\n\n");


    printf("\n\n\n SEMANA 3: ");
    NO* pai = NULL;
    NO* ancestral = NULL;
    precedente(p,0,&pai,&ancestral);
    printf("\n\n");
    NO* pai2 = NULL;
    NO* ancestral2 = NULL;
    precedente(p2,20,&pai2,&ancestral);
    printf("\n\n");



    return 0;
}
