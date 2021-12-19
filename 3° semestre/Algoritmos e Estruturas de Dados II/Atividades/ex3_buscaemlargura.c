#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <malloc.h>

typedef struct aresta {
    struct aresta* prox;
    int v; // vértice de destino da aresta
    int peso; // opcional = peso da aresta
} NO;

typedef struct vert {
    NO* inicio;
    int flag;
    bool temChave;
} VERTICE;

typedef struct {
    NO* inicio;
    NO* fim;
} FILA;


// Criação de um grafo
VERTICE* criaGrafo(int v) {
    VERTICE* grafo = (VERTICE*) malloc(v*sizeof(VERTICE));
    int i;
    for(i = 0; i < v; i++) grafo[i].inicio = NULL;
    for(i = 0; i < v; i++) grafo[i].flag = 0;
    for(i = 0; i < v; i++) grafo[i].temChave = false;
    return(grafo);
}

// Criação de uma adjacência (nó)
NO* criaAdj(int v, int peso) {
    NO* temp = (NO*) malloc(sizeof(NO));
    temp->v = v;
    temp->peso = peso;
    temp->prox = NULL;
    return(temp);
}

// Criação de uma aresta
bool criaAresta(VERTICE* grafo, int vi, int vf, int p, int v) {
    if(!grafo) return(false);
    vi--;
    vf--;

    if((vf<0)||(vf>= v))
        return false;
    if((vi<0)||(vi>= v))
        return false;

    NO* novo = criaAdj(vf,p);
    novo->prox = grafo[vi].inicio; // oiiiiiiii
    grafo[vi].inicio = novo;
    return(true);
}

// Exibição do grafo
void imprime(VERTICE* grafo, int v) {
    int i;
    for(i=0; i<v; i++) {
        printf("v%d: ", i+1);
        NO* ad = grafo[i].inicio;
        while(ad) {
            printf("v%d(%d) ", ad->v+1, grafo[i].flag);
            ad = ad->prox;
        }
        printf("\n");
    }
}

// Busca em profundidade
void prof(VERTICE* g, int i) {
    g[i].flag = 1;
    NO* p = g[i].inicio;
    //printf("passei por aqui, sou o %d \n",i+1);

    while(p) {
        if(g[p->v].flag == 0) prof(g,p->v);
        p = p->prox;
    }
    g[i].flag = 2;
}

// FUNÇÕES DE FILA

// Inicialização da fila
void inicializarFila(FILA* f) {
    f->inicio = NULL;
    f->fim = NULL;
}

// Inserir item ao final da fila dinamica
void entrarFila(FILA* f, int ch) {
    NO* novo = (NO*) malloc(sizeof(NO));
    novo->v = ch;
    novo->prox = NULL;
    if(f->fim) f->fim->prox = novo; // fila não é vazia
    else f->inicio = novo; // 1a. inserção em fila vazia
    f->fim = novo;
}

// Retirar a chave da frente ou -1
int sairFila(FILA* f) {
    NO* aux;
    int ch;
    if(!f->inicio) return(-1);
    ch = f->inicio->v;
    aux = f->inicio;
    f->inicio = f->inicio->prox;
    free(aux);
    if(!f->inicio) f->fim = NULL; // fila ficou vazia
    return(ch);
}


// Busca em largura

/*
void largura(VERTICE* g, int i) {
    FILA f;
    inicializarFila(&f);
    g[i].flag = 1;
    entrarFila(&f,i);

    while(f.inicio) {
        i = sairFila(&f);
        NO* p = g[i].inicio;

        while(p) {
            if (g[p->v].flag == 0) {
                g[p->v].flag = 1;
                entrarFila(&f,p->v);
            }
            p = p->prox;
        }
        g[i].flag = 2;
    }
}
*/


/*
EXERCÍCIO SEMANAL 3
Contexto: no mesmo grafo de salas do exemplo
anterior, suponha que as arestas são associadas a um
valor representando o custo do deslocamento de uma
sala para outra.
- Objetivo: dado um ponto de partida i, escreva um
algoritmo que retorne o custo total (i.e., a soma das
arestas) do ponto inicial i até a chave mais próxima (em
número de arestas, sem considerar seu peso). Se duas
ou mais chaves estiverem à mesma distância de i,
retorne o resultado da primeira que encontrar.
- A assinatura da função é deixada incompleta para ser
modificada a seu critério:
void custoChaveMaisProxima(VERTICE* g, int i...
*/

/*
int custoChaveMaisProxima(VERTICE* g, int i) {
    // Criação e inicialização da fila.
    FILA f;
    inicializarFila(&f);

    //O vértice inicial é marcado como visitado
    //e é colocado na fila.
    g[i].flag = 1;
    entrarFila(&f,i);

    // Custo é inicialmente igual a zero.
    int custo = 0;

    // A fila é percorrida enquanto não está vazia.
    while(f.inicio) {
        // i é removido da fila e percorremos suas
        // adjacências.

        i = sairFila(&f);
        NO* p = g[i].inicio;
        if(p && g[p->v].flag != 2) {
            printf("peso de %d do vertice %d ",p->peso,p->v);
            custo += p->peso;
        }


        NO* aux = f.inicio;
        bool naFila = false;
        while(aux && p) {
            printf("oi");
            if(aux->v == p->v) {
                    naFila = true;
                    printf("%d ",p->v);
            }
            aux = aux->prox;
        }
        if (p && (!naFila) && g[p->v].flag != 2) custo += p->peso;

        while(p) {
            // Se o vértice não foi visitado:
            if (g[p->v].flag == 0) {
                // É marcado como visitado
                g[p->v].flag = 1;
                // Seu peso é adicionado a 'custo'
                custo = custo + p->peso;
                //printf("%d ",p->v+1);
                // Se encontramos a chave:
                // Esvaziamos a fila e retornamos
                // o valor do custo.
                if(g[p->v].temChave) {
                    while(f.inicio) sairFila(&f);
                    return custo;
                }
                // Entra na fila
                entrarFila(&f,p->v);
            }
            p = p->prox;
        }

        // Todas as adjacências já foram visitadas
        g[i].flag = 2;

    }
}
*/

/*
RASCUNHO COM PRINTS (FUNCIONA)

int custoChaveMaisProxima(VERTICE* g, int i, int n) {
    FILA f;
    inicializarFila(&f);
    g[i].flag = 1;
    entrarFila(&f,i);
    int* dist = (int*) malloc(sizeof(int)*n);
    for(int i=0; i<n; i++) dist[i] = 1000;
    dist[i] = 0;

    int* distPeso = (int*) malloc(sizeof(int)*n);
    for(int i=0; i<n; i++) distPeso[i] = 1000;
    distPeso[i] = 0;

    bool* temChave = (bool*) malloc(sizeof(bool)*n);
    for(int i=0; i<n; i++) temChave[i] = false;


    while(f.inicio) {
        i = sairFila(&f);
        NO* p = g[i].inicio;

        while(p) {
            if (g[p->v].flag == 0) {
                g[p->v].flag = 1;
                dist[p->v] = dist[i] + 1;
                distPeso[p->v] = distPeso[i] + p->peso;
                if(g[p->v].temChave) {
                    while(f.inicio) sairFila(&f);
                    return distPeso[p->v];
                }
                    //temChave[p->v] = true;
                entrarFila(&f,p->v);
            }
            p = p->prox;
        }
        g[i].flag = 2;


        imprime(g,5);
        for(int i=0; i<n; i++) printf("%d ",dist[i]);
        printf("\n");
        for(int i=0; i<n; i++) {
            if(temChave[i]) printf("S ");
            else printf("N ");
        }
        printf("\n");
        for(int i=0; i<n; i++) printf("%d ",distPeso[i]);
        printf("\n\n");
    }

}

*/

int custoChaveMaisProxima(VERTICE* g, int i, int n) {
    // Criação e inicialização da fila.
    FILA f;
    inicializarFila(&f);

    //O vértice inicial é marcado como visitado
    //e é colocado na fila.
    g[i].flag = 1;
    entrarFila(&f,i);

    // Criação de um vetor a fim de armazenar os
    // pesos somados no caminho mais curto até o
    // vértice em questão. O vetor é inicializado
    // com zeros.
    int* distPeso = (int*) malloc(sizeof(int)*n);
    for(int i=0; i<n; i++) distPeso[i] = 0;

    // A fila é percorrida enquanto não está vazia.
    while(f.inicio) {
        // i é removido da fila e percorremos suas
        // adjacências.
        i = sairFila(&f);
        NO* p = g[i].inicio;

        while(p) {
            // Se o vértice não foi visitado:
            if (g[p->v].flag == 0) {
                // É marcado como visitado
                g[p->v].flag = 1;

                // A posição do array recebe o peso
                // acumulado do caminho mais o peso
                // da aresta analisada.
                distPeso[p->v] = distPeso[i] + p->peso;

                // Se encontramos a chave:
                // Esvaziamos a fila e retornamos
                // o valor do custo.
                if(g[p->v].temChave) {
                    while(f.inicio) sairFila(&f);
                    return distPeso[p->v];
                }
                // Entra na fila
                entrarFila(&f,p->v);
            }
            p = p->prox;
        }
        // Todas as adjacências já foram visitadas
        g[i].flag = 2;
    }
}


int main() {
    VERTICE* grafo = criaGrafo(5);
    criaAresta(grafo,1,3,3,5);
    criaAresta(grafo,1,2,8,5);
    criaAresta(grafo,3,2,4,5);
    criaAresta(grafo,3,5,1,5);
    criaAresta(grafo,4,2,3,5);
    criaAresta(grafo,4,3,0,5);
    criaAresta(grafo,5,4,8,5);
    grafo[1].temChave = true;
    //grafo[2].temChave = true;
    //grafo[4].temChave = true;

    // Impressão do grafo feito com lista de adjacências.
    imprime(grafo,5);
    printf("%d ",custoChaveMaisProxima(grafo,2,5));

    VERTICE* grafo2 = criaGrafo(5);
    criaAresta(grafo2,1,3,4,5);
    criaAresta(grafo2,1,2,5,5);
    criaAresta(grafo2,2,3,3,5);
    criaAresta(grafo2,3,5,1,5);
    criaAresta(grafo2,3,4,1,5);
    criaAresta(grafo2,4,2,6,5);
    criaAresta(grafo2,4,5,5,5);
    criaAresta(grafo2,5,1,2,5);
    grafo2[2].temChave = true;

    //imprime(grafo2,5);
    //printf("%d ",custoChaveMaisProxima(grafo2,3,5));
    return 0;
}
