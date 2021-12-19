#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

/*
Escreva uma função C que recebe como entrada um vetor de inteiros de N
elementos possivelmente repetidos, e verifica a ordenação dos elementos.
int verificarOrdem(int vetor[], int N)
● O retorno da função é um inteiro -1, +1, 0 ou 99 como segue:
○ +1 se os elementos seguem uma ordem crescente, ou no mínimo não decrescente
{1 2 3 4 10 20 20 20 20 33 44 55 66}
○ -1 se os elementos seguem uma ordem decrescente, ou no mínimo não crescente
{99 88 77 77 77 77 77 66 50 30 20 10 1 1 1 1 1 0}
○ 0 se os elementos são idênticos ou se a lista é vazia:
{1 1 1 1 1 1}
○ 99 caso não haja nenhuma ordem (ou seja, nenhuma das anteriores):
{1 2 3 2 4 5 6 }
*/

int verificarOrdem(int vetor[], int N) {
    char crescente = 'V';
    char decrescente = 'V';
    char iguais = 'V';

    for (int i=0; i<N-1; i++) {
        if (vetor[i] > vetor[i+1]) crescente = 'F';
        if (vetor[i] < vetor[i+1]) decrescente = 'F';
        if (vetor[i] != vetor[i+1]) iguais = 'F';
    }

    if (iguais == 'F' && crescente == 'V') return 1;
    if (iguais == 'F' && decrescente == 'V') return -1;
    if (iguais == 'V') return 0;
    return 99;
}


int main () {
    int t1 [] = {1,2,3,4,5,10,44,55,66}; // 9 elementos
    int t2 [] = {99,88,77,77,66,50,30,20,10,1,1,0}; // 12 elementos
    int t3 [] = {1,1,1,1}; // 4 elementos
    int t4 [] = {1,2,3,2,4,5,6}; // 7 elementos
    int t5 [] = {};

    printf("%i \n",verificarOrdem(t1,9));
    printf("%i \n",verificarOrdem(t2,12));
    printf("%i \n",verificarOrdem(t3,4));
    printf("%i \n",verificarOrdem(t4,7));
    printf("%i \n",verificarOrdem(t5,0));

    return 0;
}
