#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

/*
ATIVIDADE 4
Escreva um algoritmo que, dado um arquivo texto qualquer e
uma palavra a ser localizada, verifique se a palavra ocorre
ou n�o no arquivo, retornando true/false conforme o caso.
Cuidado com falsos positivos, como no caso de procurar por
"casas" e encontrar apenas "casa" etc.
*/

bool ocorrenciaDaPalavra(FILE* arq, char* palavra) {
    // Arquivo n�o encontrado
    if (!arq) return false;

    char c;
    // Vetor auxiliar para armazenar os caracteres do
    // arquivo conforme aparecem.
    char aux[30];
    // Posi��o em que o pr�ximo caractere ser� inserido
    int n = 0;
    // Vari�vel booleana que armazenar� o resultado da
    // compara��o entre a palavra atual e a palavra
    // buscada.
    bool iguais = true;

    // C�lculo do tamanho da palavra
    int tamanho = strlen(palavra);

    while(!feof(arq)) {
        c = getc(arq);
        // Caracteres alfab�ticos s�o inseridos no vetor aux
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            aux[n] = c;
        }

        // Tem-se uma palavra para ser analisada
        else {
            // Se a palavra for do mesmo tamanho e igual �
            // buscada, 'iguais' conter� true, e a fun��o
            // retorna true para indicar que foi encontrada.
            if (n == tamanho) {
                for (int i=0; i<n; i++) {
                    if (palavra[i] != aux[i])
                        iguais = false;
                }
                if (iguais) return true;
            }
            // Se a palavra n�o foi encontrada, n e 'iguais'
            // s�o reinicializados para continuar a busca.
            n = -1;
            iguais = true;
        }
        n++;
    }

    // N�o encontrada
    return false;
}

int main() {

    char nomeDoArq[20];
    char palavra[30];

    printf("Insira o nome do arquivo texto a ser lido: ");
    gets(nomeDoArq);
    if (nomeDoArq[0] == '\0') return 0;

    printf("Insira o nome da palavra buscada: ");
    gets(palavra);
    if (palavra[0] == '\0') return 0;

    FILE* arq = fopen(nomeDoArq,"rb");

    bool resposta = ocorrenciaDaPalavra(arq,palavra);

    fclose(arq);

    return 0;
}
