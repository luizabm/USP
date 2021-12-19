#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <malloc.h>

// Elemento da lista
typedef struct estr {
        int valor;
        struct estr* prox;
} NO;


// Função principal
NO* uniao(NO* p1, NO* p2);

/*
INSERÇÃO DE UM ELEMENTO NA LISTA LIGADA
----------------------------------------------------------
Função auxiliar criada com o propósito de inserir chaves na
lista passada por parâmetro, permitindo, porém, duplicações.
Os parâmetros são a chave a ser inserida e a lista (passagem
por referência). A função é do tipo void, sem retorno.
- Cria-se um novo nó e adiciona-se a chave. Posteriormente,
realiza-se uma busca sequencial a fim de determinar o nó
imediatamente anterior ao que será inserido, mantendo a lista
em ordem crescente.
- 3 casos são considerados: O caso em que a lista está vazia,
tratando-se da primeira inserção; o caso em que o nó em questão
será inserido no início; e, por fim, o caso genérico de inserção
após um nó existente.
*/
void inserirElem(int chave, NO** lista) {
    NO* novo = (NO*) malloc(sizeof(NO));
    novo->valor = chave;

    // Busca sequencial
    NO* p = *lista;
    NO* ant = NULL;
    while (p) {
        if (p->valor >= chave) break;
        ant = p;
        p = p->prox;
    }

    // 3 casos considerados de inserção
    if(!lista) { // Lista vazia (primeira inserção)
        *lista = novo;
        novo->prox = NULL;
    }

    else if(!ant) { // Inserção no início da lista
        novo->prox = *lista;
        *lista = novo;
    }

    else { // Inserção após um nó já existente
        novo->prox = ant->prox;
        ant->prox = novo;
    }
}

/*
BUSCA SEQUENCIAL NA LISTA LIGADA
--------------------------------------------------------
Função auxiliar responsável por buscar determinada chave,
passada por parâmetro, em uma lista ligada. Se a chave
for encontrada e diferente de NULL, o NO* contendo sua
referência é retornado. Se não existir na lista, NULL é
retornado.
*/
NO* busca(int chave, NO* lista) {
    NO* b = lista;
    while (b) {
        if (b->valor == chave) break;
        b = b->prox;
    }
    if (b && (b->valor == chave)) return b;
    return NULL;
}

/*
BUSCA E INSERÇÃO DE UM ELEMENTO NA LISTA SEM REPETIÇÃO
------------------------------------------------------
Função auxiliar que utiliza as duas funções anteriores.
Recebe uma lista a ser percorrida, e uma lista de
resposta - na qual os elementos da lista percorrida
serão inseridos em ordem crescente e exclusivamente no
caso em que não estão presentes na lista de resposta.
*/
void buscaInsercao(NO** lista, NO** listaResp) {
    NO* p = *lista;
    while(p) {
        if (!busca(p->valor,*listaResp)) inserirElem(p->valor,listaResp);
        p = p->prox;
    }
}

//------------------------------------------
// O EP consiste em implementar esta funcao
// e outras funcoes auxiliares que esta
// necessitar.
//------------------------------------------
NO* uniao(NO* p1, NO* p2) {

	NO* resp;
	resp = NULL;

	if (!p1 && !p2) return resp;

    if (!p1 && p2) buscaInsercao(&p2,&resp);

    if (p1 && !p2) buscaInsercao(&p1,&resp);

    if (p1 && p2) {
        buscaInsercao(&p1,&resp);

        buscaInsercao(&p2,&resp);
    }

	return resp;
}

//----------------------------------------------------------------
// use main() apenas para fazer chamadas de teste ao seu programa
//----------------------------------------------------------------
int main() {

	NO* p1 = NULL;
	NO* p2 = NULL;

	// aqui vc pode incluir codigo para inserir elementos
	// de teste nas listas p1 e p2
	// Inserção de elementos na lista 1
    for (int i=0; i<30; i++) {
        int aux = rand()%100;
        inserirElem(aux,&p1);
    }

    // Inserção de elementos na lista 2
    for (int i=0; i<30; i++) {
        int aux = rand()%100;
        inserirElem(aux,&p2);
    }

    // Exibição das listas
    NO* it1 = p1;
    NO* it2 = p2;
    printf("\n Lista 1: \n");
    while (it1) {
        printf("%d ",it1->valor);
        it1 = it1->prox;
    }
    printf("\n Lista 2: \n");
    while (it2) {
        printf("%d ",it2->valor);
        it2 = it2->prox;
    }

	// o EP sera testado com chamadas deste tipo
	NO* teste = NULL;
	teste = uniao(p1,p2);
	printf("\n União das listas 1 e 2: \n");
	while (teste) {
        printf("%d ",teste->valor);
        teste = teste->prox;
    }
}

// por favor nao inclua nenhum código abaixo da função main()
