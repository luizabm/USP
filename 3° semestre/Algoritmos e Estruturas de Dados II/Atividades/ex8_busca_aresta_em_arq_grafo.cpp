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

/*
ATIVIDADE 8
Suponha o mesmo arquivo de registros de tamanho fixo (bin�rio) da
semana anterior, em que cada registro � um par de arestas (v1,v2)
e um custo, ou seja:

typedef struc {
	int v1;
	int v2;
	int custo;
} REGISTRO;

Escreva um algoritmo que, dado um par de v�rtices v1,v2 e um arquivo
de grafo do tipo acima, retorne o seu custo ou, se a aresta n�o
existir, retorne -1. Por simplicidade, considere que os v�rtices
poss�veis s�o numerados de 0 a 9.
*/

int custoDaAresta(FILE* arq, int v1, int v2) {
    REGISTRO r; // Auxiliar

    // Leitura de um registro por vez
    while (fread(&r,sizeof(REGISTRO),1,arq) == 1)
        if (r.v1 == v1 && r.v2 == v2) // Aresta encontrada
            return r.custo;

    return -1; // Aresta n�o existe
}

int main() {
    char nomeDoArq[20];
    int v1;
    int v2;
    int custo;

    // Obten��o do nome do arquivo
    printf("Insira o nome do arquivo texto a ser lido: ");
    gets(nomeDoArq);
    if (nomeDoArq[0] == '\0') return 0;

    // Obten��o do par de v�rtices
    printf("Insira o valor desejado para v1: ");
    scanf("%d",&v1);
    printf("Insira o valor desejado para v2: ");
    scanf("%d",&v2);

    // Abertura do arquivo (modo de leitura)
    FILE* arq = fopen(nomeDoArq,"rb");

    // Chamada � fun��o respons�vel pela obten��o do custo
    if (arq) {
        custo = custoDaAresta(arq,v1,v2);
        printf("%d",custo);
    }

    // Fechamento do arquivo
    fclose(arq);

    return 0;
}
