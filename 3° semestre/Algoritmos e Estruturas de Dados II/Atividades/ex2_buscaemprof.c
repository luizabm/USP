#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <malloc.h>

typedef struct aresta {
    struct aresta* prox;
    int v; // v�rtice de destino da aresta
    //int peso; // opcional = peso da aresta
} NO;

typedef struct vert {
    NO* inicio;
    int flag;
    bool temChave;
} VERTICE;

// Cria��o de um grafo
VERTICE* criaGrafo(int v) {
    VERTICE* grafo = (VERTICE*) malloc(v*sizeof(VERTICE));
    int i;
    for(i = 0; i < v; i++) grafo[i].inicio = NULL; //aqui
    for(i = 0; i < v; i++) grafo[i].flag = 0;
    for(i = 0; i < v; i++) grafo[i].temChave = false;
    return(grafo);
}

// Cria��o de uma adjac�ncia (n�)
NO* criaAdj(int v) {
    NO* temp = (NO*) malloc(sizeof(NO));
    temp->v = v;
    //temp->peso = peso;
    temp->prox = NULL;
    return(temp);
}

// Cria��o de uma aresta
bool criaAresta(VERTICE* grafo, int vi, int vf, int v) {
    if(!grafo) return(false);
    vi--;
    vf--;

    if((vf<0)||(vf>= v))
        return false;
    if((vi<0)||(vi>= v))
        return false;

    NO* novo = criaAdj(vf);
    novo->prox = grafo[vi].inicio; // oiiiiiiii
    grafo[vi].inicio = novo;
    return(true);
}

// Exibi��o do grafo
void imprime(VERTICE* grafo, int v) {
    if (!grafo) return;
    int i;
    for(i=0; i<v; i++) {
        printf("v%d: ", i+1);
        NO* ad = grafo[i].inicio;
        while(ad) {
            printf("v%d ", ad->v+1);
            ad = ad->prox;
        }
        printf("\n");
    }
}

/*
 Busca em profundidade
void prof(VERTICE* g, int i) {
    g[i].flag = 1;
    NO* p = g[i].inicio;

    while(p) {
        if(g[p->v].flag == 0) prof(g,p->v);
        p = p->prox;
    }
    g[i].flag = 2;
}
*/

/*
Contexto: no mesmo grafo de salas do exemplo a ser visto em aula,
suponha que pode existir chaves simultaneamente em v�rias salas,
e n�o apenas em uma.
Objetivo: dado um ponto de partida i, escreva um algoritmo que
retorne uma lista ligada contendo todas as salas alcan��veis a
partir de i que possuem chave, em qualquer ordem.
A assinatura da fun��o � deixada incompleta para ser modificada
a seu crit�rio:
       void salasComChaves(VERTICE* g, int i.......
*/
void salasComChaves(VERTICE* g, int i, NO** lista) {
    g[i].flag = 1; // visitado

    /*
    Se a sala possuir chave, criamos um novo n� e o
    adicionamos no in�cio da lista ligada.
    */
    if (g[i].temChave) {
        NO* novo = (NO*) malloc(sizeof(NO));
        novo->v = i;
        novo->prox = *lista;
        *lista = novo;
    }

    /*
    Percorremos as adjac�ncias e visitamos seus v�rtices
    de destino caso j� n�o tenham sido visitados.
    */
    NO* p = g[i].inicio;
    while(p) {
        if(g[p->v].flag == 0) salasComChaves(g,p->v,lista);
        p = p->prox;
    }

    /*
    Se todas as adjac�ncias de um v�rtice j� tiverem sido
    visitadas, retrocedemos.
    */
    g[i].flag = 2;
}


int main() {
    VERTICE* grafo = criaGrafo(5);
    criaAresta(grafo,1,3,5);
    criaAresta(grafo,1,2,5);
    criaAresta(grafo,3,2,5);
    criaAresta(grafo,3,5,5);
    criaAresta(grafo,4,2,5);
    criaAresta(grafo,4,3,5);
    criaAresta(grafo,5,4,5);
    //grafo[0].temChave = true;
    //grafo[1].temChave = true;
    //grafo[2].temChave = true;
    //grafo[4].temChave = true;
    for(int i = 0; i < 5; i++) grafo[i].temChave = true;

    // Impress�o do grafo feito com lista de adjac�ncias.
    imprime(grafo,5);

    NO* lista = NULL;
    salasComChaves(grafo,0,&lista);

    printf("\n\n");

    while(lista) {
        printf("%d ",lista->v);
        lista = lista->prox;
    }


    return 0;
}
