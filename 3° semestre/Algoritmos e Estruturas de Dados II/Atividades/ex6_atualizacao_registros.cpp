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

/*
ATIVIDADE 6
Usando o struct da aula arquivos parte 3, escreva um programa
que recebe como entrada um arquivo com registros deste tipo
(ou seja, de tamanho fixo) e dois endereços (bytes iniciais)
de registro r1 e r2, e faça a troca destes dois registros,
ou seja, escrevendo r1 na posição r2 e vice-versa.

Lembre-se de que o primeiro registro está na posição (byte)
zero do arquivo.
*/

void trocaRegistros(FILE* arq, int byte1, int byte2) {
    tipo_registro aux;
    tipo_registro aux2;

    // Armazenamento do registro r1 em aux
    fseek(arq,byte1,SEEK_SET);
    fread(&aux,sizeof(tipo_registro),1,arq);

    // Armazenamento do registro r2 em aux2
    fseek(arq,byte2,SEEK_SET);
    fread(&aux2,sizeof(tipo_registro),1,arq);

    // Escrita de r2 em r1
    fseek(arq,byte1,SEEK_SET);
    fwrite(&aux2,sizeof(tipo_registro),1,arq);

    // Escrita de r1 em r2
    fseek(arq,byte2,SEEK_SET);
    fwrite(&aux,sizeof(tipo_registro),1,arq);
}


int main() {
    char nomeDoArq[20];
    int byte1;
    int byte2;

    // Nome do arquivo
    printf("Insira o nome do arquivo texto a ser lido: ");
    gets(nomeDoArq);
    if (nomeDoArq[0] == '\0') return 0;

    // Bytes iniciais de r1 e r2
    printf("Insira o byte inicial de r1: ");
    scanf("%d",&byte1);
    printf("Insira o byte inicial de r2: ");
    scanf("%d",&byte2);

    // Abertura do arquivo no modo leitura + escrita
    FILE* arq = fopen(nomeDoArq,"r+");

    // Troca dos registros
    if (arq) trocaRegistros(arq,byte1,byte2);

    // Fechamento do arquivo
    fclose(arq);

    return 0;
}
