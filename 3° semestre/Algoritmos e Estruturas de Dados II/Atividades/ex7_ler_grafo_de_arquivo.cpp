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
    int v; // v�rtice de destino da aresta
    int peso; // peso da aresta
} NO;

// V�rtices
typedef struct vert {
    NO* inicio; // in�cio da lista de adjac�ncias
} VERTICE;

/*
ATIVIDADE 7
Suponha um arquivo de registros de tamanho fixo (bin�rio) em que
cada registro � um par de arestas (v1,v2) e um custo, ou seja:

typedef struct {
	int v1;
	int v2;
	int custo;
} REGISTRO;

Escreva um algoritmo para ler um arquivo deste tipo e construir o
grafo correspondente, retornando a respectiva ED de listas de
adjac�ncias. Por simplicidade, considere que os v�rtices
poss�veis s�o numerados de 0 a 9.
*/

VERTICE* constroiGrafo(FILE* arq) {
    // Cria��o e inicializa��o do grafo
    VERTICE* g = (VERTICE*) malloc(10 * sizeof(VERTICE));
    for(int i = 0; i <= 9; i++) g[i].inicio = NULL;

    REGISTRO aux;
    NO* novo;

    // Leitura de um registro por vez no arquivo
    while (fread(&aux,sizeof(REGISTRO),1,arq) == 1) {
        // Cria��o da adjac�ncia
        novo = (NO*) malloc(sizeof(NO));
        novo->v = aux.v2;
        novo->peso = aux.custo;

        // Inser��o na lista de adjac�ncias
        novo->prox = g[aux.v1].inicio;
        g[aux.v1].inicio = novo;
    }

    return g;
}

// Exibi��o do grafo
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

    // Constru��o do grafo
    VERTICE* g;
    if (arq) g = constroiGrafo(arq);
    imprime(g,10);

    // Fechamento do arquivo
    fclose(arq);

    return 0;
}
