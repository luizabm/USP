#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

// Registros do aluno
struct registro {
    int nota;
    char nome[20];
};

/*
ATIVIDADE 5
Escreva um programa que recebe como entrada o arquivo
de registros de tamanho variável com delimitadores
(ver aula arquivos parte 1, no exemplo de cadastro
de alunos e notas) e o converte para o formato de
registros de tamanho fixo, criando um novo arquivo
deste tipo.
*/

FILE* arqTamanhoFixo(FILE* arq) {
    int prox = 0;

    if (!arq) return NULL; // Arquivo não encontrado

    struct registro dadosAlunos[1000]; // Array de structs

    while (!feof(arq)) {
        // Obtenção do nome do aluno e armazenamento no array
        fscanf(arq, "%[^/]%*c", dadosAlunos[prox].nome);
        // Obtenção da nota do aluno e armazenamento no array
        fscanf(arq,"%d\n", &dadosAlunos[prox].nota);
        prox++;
    }

    // Criação do arquivo e escrita dos dados
    FILE* novoArq = fopen("teste.txt","wb");
    int i = fwrite(dadosAlunos,sizeof(registro),prox,novoArq);

    return novoArq;
}

int main() {
    // Obtenção de input para o nome do arquivo
    char nomeDoArq[20];
    printf("Insira o nome do arquivo texto a ser lido: ");
    gets(nomeDoArq);
    if (nomeDoArq[0] == '\0') return 0;

    FILE* arq = fopen(nomeDoArq,"rb");

    FILE* novoArq = arqTamanhoFixo(arq);

    // Fechamento dos arquivos
    fclose(arq);
    fclose(novoArq);

    return 0;
}
