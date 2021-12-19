#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

// Registros
typedef struct {
	int v1;
	int v2;
	int custo;
} REGISTRO;

// Arestas
typedef struct aresta {
    struct aresta* prox;
    int v; // vértice de destino da aresta
    int peso; // peso da aresta
} NO;

// Vértices
typedef struct vert {
    NO* inicio; // início da lista de adjacências
} VERTICE;

/*
ATIVIDADE 7
Suponha um arquivo de registros de tamanho fixo (binário) em que
cada registro é um par de arestas (v1,v2) e um custo, ou seja:

typedef struct {
	int v1;
	int v2;
	int custo;
} REGISTRO;

Escreva um algoritmo para ler um arquivo deste tipo e construir o
grafo correspondente, retornando a respectiva ED de listas de
adjacências. Por simplicidade, considere que os vértices
possíveis são numerados de 0 a 9.
*/

VERTICE* constroiGrafo(FILE* arq) {
    // Criação e inicialização do grafo
    VERTICE* g = (VERTICE*) malloc(10 * sizeof(VERTICE));
    for(int i = 0; i <= 9; i++) g[i].inicio = NULL;

    REGISTRO aux;
    NO* novo;

    // Leitura de um registro por vez no arquivo
    while (fread(&aux,sizeof(REGISTRO),1,arq) == 1) {
        // Criação da adjacência
        novo = (NO*) malloc(sizeof(NO));
        novo->v = aux.v2;
        novo->peso = aux.custo;

        // Inserção na lista de adjacências
        novo->prox = g[aux.v1].inicio;
        g[aux.v1].inicio = novo;
    }

    return g;
}

// Exibição do grafo
void imprime(VERTICE* grafo, int v) {
    int i;
    for(i=0; i<v; i++) {
        printf("v%d: ", i+1);
        NO* ad = grafo[i].inicio;
        while(ad) {
            printf("v%d(%d) ", ad->v, ad->peso);
            ad = ad->prox;
        }
        printf("\n");
    }
}

int main() {
    char nomeDoArq[20];

    // Nome do arquivo
    printf("Insira o nome do arquivo texto a ser lido: ");
    gets(nomeDoArq);
    if (nomeDoArq[0] == '\0') return 0;

    // Abertura do arquivo no modo de leitura
    FILE* arq = fopen(nomeDoArq,"rb");

    // Construção do grafo
    VERTICE* g;
    if (arq) g = constroiGrafo(arq);
    imprime(g,10);

    // Fechamento do arquivo
    fclose(arq);

    return 0;
}
