#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

// Registros
struct tipo_registro {
    char nrousp[7];
    char nome[20];
    int idade;
    int valido; // 1=ok; 0=excluido.
};

void Exibir(struct tipo_registro vetor_alunos[], int proximo){
    int i;
    printf("\n--------------------------------------\n");
    printf("Ha %d alunos cadastrados.\n", proximo);
    for (i=0; i< proximo; i++) {
        printf("\n%7s ", vetor_alunos[i].nrousp);
        printf("%20s ", vetor_alunos[i].nome);
        printf("%d", vetor_alunos[i].idade);
    }
    printf("\n--------------------------------------\n");
}

int main (){
    int i;
    char c;
    char codigo[7];
    FILE *arq;
    struct tipo_registro vetor_alunos[30];
    int proximo = 0; // contador de elementos da estrutura

    // VERIFICA SE HA DADOS PRE-GRAVADOS
    if ((arq=fopen("ex6_novo.dad","rb"))==NULL) {
        printf("Arquivo nao encontrado...\n");
    }
    else {
        // tenta ler até MAX registros de uma vez
        proximo = fread(vetor_alunos, sizeof(tipo_registro), 30, arq);
        if (proximo < 1) printf("Arquivo vazio...\n");
        fclose(arq);
    }
    // recebe os dados via teclado e atualiza o contador 'proximo'
    do {
        Exibir(vetor_alunos, proximo);
        printf("\nInforme o nome do aluno:");
        fflush(stdin);
        gets(vetor_alunos[proximo].nome);
        if (vetor_alunos[proximo].nome[0]=='z') break;
        printf("\nInforme o nro. USP:");
        fflush(stdin);
        gets(vetor_alunos[proximo].nrousp);
        //if (vetor_alunos[proximo].nrousp[0]==0) break;
        printf("\nInforma a idade:");
        fflush(stdin);
        scanf("%d", &vetor_alunos[proximo].idade);
        proximo++;
    } while (proximo < 30);
    Exibir(vetor_alunos, proximo);

    // grava dados em arquivo e encerra
    arq = fopen("ex6_novo.dad","wb");
    i = fwrite(vetor_alunos, sizeof(tipo_registro),proximo,arq);
    fclose(arq);
    printf("\nTecle algo para encerrar...");
    c = getchar();
    Exibir(vetor_alunos,i);
    return 0;
}
