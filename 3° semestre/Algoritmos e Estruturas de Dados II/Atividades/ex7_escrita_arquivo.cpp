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

void Exibir(REGISTRO grafo[], int proximo){
    int i;
    printf("\n--------------------------------------\n");
    printf("Ha %d arestas cadastradas.\n", proximo);
    for (i=0; i< proximo; i++) {
        printf("%d ", grafo[i].v1);
        printf("%d ", grafo[i].v2);
        printf("%d ", grafo[i].custo);
    }
    printf("\n--------------------------------------\n");
}

int main (){
    int i;
    char c;
    //char codigo[7];
    FILE *arq;
    REGISTRO grafo[30];
    int proximo = 0; // contador de elementos da estrutura

    // VERIFICA SE HA DADOS PRE-GRAVADOS
    if ((arq=fopen("ex8.dad","rb"))==NULL) {
        printf("Arquivo nao encontrado...\n");
    }
    else {
        // tenta ler até MAX registros de uma vez
        proximo = fread(grafo, sizeof(REGISTRO), 30, arq);
        if (proximo < 1) printf("Arquivo vazio...\n");
        fclose(arq);
    }
    // recebe os dados via teclado e atualiza o contador 'proximo'
    do {
        Exibir(grafo, proximo);
        printf("\nInforme v1:");
        fflush(stdin);
        scanf("%d", &grafo[proximo].v1);

        if (grafo[proximo].v1 == -1) break;

        printf("\nInforme v2:");
        fflush(stdin);
        scanf("%d", &grafo[proximo].v2);

        printf("\nInforme o peso:");
        fflush(stdin);
        scanf("%d", &grafo[proximo].custo);

        proximo++;
    } while (proximo < 30);
    Exibir(grafo, proximo);

    // grava dados em arquivo e encerra
    arq = fopen("ex8.dad","wb");
    i = fwrite(grafo, sizeof(REGISTRO),proximo,arq);
    fclose(arq);
    printf("\nTecle algo para encerrar...");
    c = getchar();
    Exibir(grafo,i);
    return 0;
}
