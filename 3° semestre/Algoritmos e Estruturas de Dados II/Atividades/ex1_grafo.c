#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <malloc.h>

typedef struct aresta {
    struct aresta* prox;
    int v; // vértice de destino da aresta
    //int peso; // opcional = peso da aresta
} NO;

typedef struct vert {
    NO* inicio;
} VERTICE;

// Criação de um grafo
VERTICE* criaGrafo(int v) {
    VERTICE* grafo = (VERTICE*) malloc(v*sizeof(VERTICE));
    int i;
    for(i = 0; i < v; i++) grafo[i].inicio = NULL; //aqui
    return(grafo);
}

// Criação de uma adjacência (nó)
NO* criaAdj(int v) {
    NO* temp = (NO*) malloc(sizeof(NO));
    temp->v = v;
    //temp->peso = peso;
    temp->prox = NULL;
    return(temp);
}

// Criação de uma aresta
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

// Exibição do grafo
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
Uma forma alternativa de representar
um grafo é por meio de uma lista de
incidências. Nesta representação, utilizamos o
mesmo vetor de vértices da implementação vista;
no entanto, ao invés de criarmos uma lista de
elementos adjacentes de cada vértice, criamos a
lista dos elementos que incidem sobre cada um.

Dada uma estrutura de listas de
adjacências, transforme-a em uma estrutura de
listas de incidências.
void adjacencia2incidencia(VERTICE* g, int n)
*/



/*
void adjacencia2incidencia(VERTICE** g, int n) {
    VERTICE* gr = *g;
    if(!gr) return;
    VERTICE* aux = (VERTICE*) malloc(sizeof(VERTICE)*n);
    for(int i=0; i<n; i++) aux[i].inicio = NULL;

    for(int i=0; i<n; i++) {
        NO* adj = gr[i].inicio;
        NO* temp = NULL;
        while(adj) {
            NO* novo = (NO*) malloc(sizeof(NO));
            novo->v = i;
            novo->prox = aux[adj->v].inicio;
            aux[adj->v].inicio = novo;

            temp = adj;
            adj = adj->prox;
            free(temp);
        }
    }

    *g = aux;

}
*/
void adjacencia2incidencia(VERTICE* g, int n) {
    // Se o grafo não existir, retornamos.
    if(!g) return;

    // Alocação de memória para um grafo auxiliar.
    VERTICE* aux = (VERTICE*) malloc(sizeof(VERTICE)*n);
    // Preenchimento do vetor auxiliar com NULL.
    for(int i=0; i<n; i++) aux[i].inicio = NULL;

    // O grafo original é percorrido.
    for(int i=0; i<n; i++) {
        NO* adj = g[i].inicio;
        NO* temp = NULL;
        while(adj) {
            // Criação de uma nova adjacência.
            NO* novo = (NO*) malloc(sizeof(NO));
            // Seu vértice de destino é a posição atual do vetor.
            novo->v = i;
            // Inserção no início da lista, na posição do vetor
            // correspondente à que era antes o vértice de destino.
            novo->prox = aux[adj->v].inicio;
            aux[adj->v].inicio = novo;

            // Liberação de memória das listas ligadas do grafo
            // original.
            temp = adj;
            adj = adj->prox;
            free(temp);
        }
    }
    // Listas de adjacência do grafo anterior passam a ser as do
    // novo grafo criado.
    for(int i=0; i<n; i++) g[i].inicio = aux[i].inicio;
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

    // Impressão do grafo feito com lista de adjacências.
    imprime(grafo,5);

    adjacencia2incidencia(grafo,5);
    printf("\n\n");
    imprime(grafo,5);

    return 0;
}
