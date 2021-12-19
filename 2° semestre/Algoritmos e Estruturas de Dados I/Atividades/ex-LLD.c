#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <malloc.h>

typedef struct estrutura {
    int chave;
    int info;
    struct estrutura *prox;
} NO;

typedef struct {
    NO* inicio;
} LISTA;

// Inicializa��o
void inicializarLista(LISTA* l) {
    l->inicio = NULL;
}
// Exibi��o da lista completa
void exibirLista(LISTA l) {
    NO* p = l.inicio;
    while (p) {
        printf("%d ",p->chave);
        p = p->prox;
    }
}

// Quantos elementos existem na lista
int tamanhoLista(LISTA l) {
    NO* p = l.inicio;
    int tam = 0;
    while (p) {
        tam++;
        p = p->prox;
    }
    return(tam);
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

// Inser��o da chave ch na lista ordenada sem duplica��es
bool inserirElemListaOrd(int ch, LISTA* l) {
    NO* novo;
    NO* ant;
    novo = buscaSeqOrd(ch, *l, &ant);
    // if(novo) return(false);
    novo = (NO*) malloc(sizeof(NO));
    novo->chave = ch;

    if(!l->inicio) { // 1a. inser��o em lista vazia
        l->inicio = novo;
        novo->prox = NULL;
    }

    else {
        if(!ant) { // inser��o no in�cio da lista
            novo->prox = l->inicio;
            l->inicio = novo;
        }

        else { // inser��o ap�s um n� existente
            novo->prox = ant->prox;
            ant->prox = novo;
        }
    }
    return(true);
}

// Exclus�o da chave dada
bool excluirElemLista(int ch, LISTA* l) {
    NO* ant;
    NO* elem;
    elem = buscaSeqOrd(ch, *l, &ant);
    if(!elem) return(false); // nada a excluir
    if(!ant) l->inicio = elem->prox; // exclui 1o. elemento da lista
    else ant->prox = elem->prox; // exclui elemento que possui ant
    free(elem); // exclus�o �f�sica�
    return(true);
}

// Destrui��o da lista
void destruirLista (LISTA* l) {
    NO* atual;
    NO* prox;
    atual = l->inicio;
    while (atual) {
        prox = atual->prox; // guarda pr�xima posi��o
        free(atual); // libera mem�ria apontada por atual
        atual = prox;
    }
    l->inicio = NULL; // ajusta in�cio da lista (vazia)
}

/*
TAREFAS
1. Dada uma lista ligada din�mica l n�o ordenada que admite repeti��o de chaves, e um
valor de chave x, retorne o n�mero de vezes que x aparece na lista.
int ocorrencias(LISTA* l, int x)

2. Verifique se duas listas ligadas din�micas l1 e l2 s�o id�nticas (i.e., com as mesmas
chaves, na mesma ordem e com o mesmo tamanho), retornando true/false conforme o
caso.
bool identicas(LISTA* l1, LISTA *l2)
*/

int ocorrencias(LISTA* l, int x) {
    int contador = 0;
    NO* p = l->inicio;
    if(!p) return contador;

    while(p) {
        if (p->chave == x) contador++;
        p = p->prox;
    }
    return contador;
}

bool identicas(LISTA* l1, LISTA* l2) {
    NO* t1 = l1->inicio;
    NO* t2 = l2->inicio;
    int tam1 = 0;
    int tam2 = 0;

    while (t1) {
        tam1++;
        t1 = t1->prox;
    }

    while (t2) {
        tam2++;
        t2 = t2->prox;
    }

    if (tam1 != tam2) return false;
    NO* p1 = l1->inicio;
    NO* p2 = l2->inicio;

    while (p1) {
        if (p1->chave != p2->chave) return false;
        p1 = p1->prox;
        p2 = p2->prox;
    }
    return true;
}

/*
TAREFAS - semana seguinte
1. Dada uma lista ligada din�mica l n�o ordenada que admite repeti��o de chaves, e um
valor de chave x, excluir todas as ocorr�ncias de x na lista.
void ExcluirOcorrencias(LISTA* l, int x)

2. Dada uma lista ligada din�mica apontada por *p, crie uma c�pia da mesma (usando
um malloc para cada elemento e fazendo as devidas liga��es), e retorne um novo
ponteiro indicando o come�o da lista assim criada.
NO* copia(NO* p)
*/


void excluir(LISTA* l, int x){
    NO* ant = NULL;
    NO* atual = l->inicio;
    NO* prox;

    while (atual) {
        prox = atual->prox;
        // anterior
        if (atual->chave == x) {
            if (!ant) l->inicio = atual->prox;
            else ant->prox = atual->prox;
            free(atual);
        }
        ant = atual;
        atual = prox;
    }
}


void excluirOcorrencias(LISTA* l, int x) {
    NO* atual = l->inicio;
    NO* ant = NULL;

    // Caso em que o primeiro n� cont�m x:
    if (atual && atual->chave == x) {
        l->inicio = atual->prox;
        free(atual);
        atual = l->inicio;
    }

    // Outras ocorr�ncias:
    while (atual) {
        while (atual && atual->chave != x) {
            ant = atual;
            atual = atual->prox;
        }
        if (!atual) return; // x n�o est� na lista

        ant->prox = atual->prox;
        free(atual);
        atual = ant->prox;
    }
}

void ExcluirOcorrencias(LISTA *l, int x) {
    NO* ref = l->inicio;
    NO* ant = NULL;

    if (l->inicio != NULL) {
        while (ref != NULL) {
            NO* ref2 = ref->prox;
            if (ant->prox->chave == x){
            free(ref);
            }
        ant->prox = ref2;
        }
    }
}

NO* copia(NO* p) {
    NO* novaLista = NULL;
    NO* aux = NULL;
    NO* atual = p;

    // Primeiro n�:
    if (atual) {
        novaLista = (NO*) malloc(sizeof(NO));
        novaLista->chave = atual->chave;
        novaLista->prox = NULL;
        atual = atual->prox;
    }

    aux = novaLista;

    // Demais n�s:
    while (atual) {
        aux->prox = (NO*) malloc(sizeof(NO));
        aux = aux->prox;
        aux->chave = atual->chave;
        aux->prox = NULL;
        atual = atual->prox;
    }

    return novaLista;
}

int main() {
 // Declara��o e inicializa��o da lista ligada
    LISTA teste1;
    LISTA teste2;
    LISTA teste3;
    inicializarLista(&teste1);
    inicializarLista(&teste2);
    inicializarLista(&teste3);

    // Inser��o de elementos nas listas 1 e 2
    for (int i = 0; i<50; i++) {
        int aux = rand()%50;
        inserirElemListaOrd(aux,&teste1);
        inserirElemListaOrd(aux,&teste2);
    }

    // Inser��o de elementos na lista 3
    for (int i = 0; i<20; i++) {
        int aux = rand()%50;
        inserirElemListaOrd(aux,&teste3);
    }

    // Exibi��o das listas antes da execu��o dos m�todos
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
    printf("\n\n Teste do m�todo c�pia: \n");
    NO* aux = copia(teste1.inicio);
    NO* aux2 = copia(teste2.inicio);
    NO* aux3 = copia(teste3.inicio);
    while (aux) {
        printf("%d ",aux->chave);
        aux = aux->prox;
    }
    printf("\n");
    while (aux2) {
        printf("%d ",aux2->chave);
        aux2 = aux2->prox;
    }
    printf("\n");
    while (aux3) {
        printf("%d ",aux3->chave);
        aux3 = aux3->prox;
    }

    // Teste de excluirOcorrencias() e exibi��o:
    printf(" \n\n Teste do m�todo de excluir: \n");
    ExcluirOcorrencias(&teste1,3);
    ExcluirOcorrencias(&teste2,11);
    ExcluirOcorrencias(&teste3,40);


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

