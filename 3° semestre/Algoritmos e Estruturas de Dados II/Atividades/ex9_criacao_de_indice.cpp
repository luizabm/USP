#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

// Registros do arquivo
typedef struct {
	int v1;
	int v2;
	int custo;
} REGISTRO;

// Tabela de índices
typedef struct {
    int v1;
    int v2;
    int nroRegistro;
} TABELA;

/*
ATIVIDADE 9
Suponha o mesmo arquivo de registros de tamanho fixo (binário)
da semana anterior, em que cada registro é um par de arestas
(v1,v2) e um custo.

Escreva um algoritmo que, dado um arquivo deste tipo, crie uma
tabela de índices em memória usando um vetor estático comum do
tipo struct de 3 campos (v1, v2 e o nro. do registro no
arquivo).

Por simplicidade, considere que o número máximo de arestas
possível é 100, e observe que o acesso a uma aresta precisa
ser feito por duas chaves simultaneamente, e não por uma
chave única como nos exemplos vistos em aula.
*/

int main() {
    // Obtenção do nome do arquivo
    char nomeDoArq[20];
    printf("Insira o nome do arquivo texto a ser lido: ");
    gets(nomeDoArq);
    if (nomeDoArq[0] == '\0') return 0;

    // Abertura do arquivo (modo de leitura)
    FILE* arq = fopen(nomeDoArq,"rb");

    TABELA indices[100]; // Tabela de índices
    REGISTRO r; // Registro auxiliar
    int prox = 0; // Número do registro atual

    // Criação dos índices em memória principal
    if (arq) {
        // Leitura de um registro por vez
        while (fread(&r,sizeof(REGISTRO),1,arq)) {
            // Preenchimento dos campos da tabela
            indices[prox].v1 = r.v1;
            indices[prox].v2 = r.v2;
            indices[prox].nroRegistro = prox;
            prox++; // Atualização do número do registro
        }
    }

    // Fechamento do arquivo
    fclose(arq);

    return 0;
}
