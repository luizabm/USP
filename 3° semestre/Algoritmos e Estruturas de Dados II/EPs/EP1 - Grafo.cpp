#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <malloc.h>

//-------------------------------------------

// nos das listas de adjacencias
typedef struct adj {
	int v;
	struct adj* prox;
} NO;

// vertices
typedef struct {
	NO* inicio;
} VERTICE;


// funcao principal
NO* caminhos_max_d(VERTICE* g, int n, int x, int y, int d);


/*
Função auxiliar que recebe uma lista, representada por seu
nó inicial, e um vértice, inserindo-o ao final da lista
ligada.
*/
void inserirElem(NO** lista, int vertice) {

    // Criação do novo nó a ser inserido
    NO* novo = (NO*) malloc(sizeof(NO));
    novo->v = vertice;
    novo->prox = NULL;

    NO* aux = NULL;

    // Já existem elementos na lista
    if (*lista) {
        aux = *lista;
        while (aux) {
            if (!aux->prox) break;
            aux = aux->prox;
        }
        aux->prox = novo; // Inserção ao final
    }
    else *lista = novo; // Lista era vazia
}

/*
Função auxiliar que recebe uma lista principal, uma
outra lista, e insere a segunda ao final da lista
principal. Para isso, utiliza a função inserirElem.
*/
void concatenaLista(NO** listaPrincipal, NO** lista) {
    NO* p = *lista;
    while(p) {
        inserirElem(listaPrincipal, p->v);
        p = p->prox;
    }
}

/*
Função auxiliar que recebe uma lista e exclui o
último elemento presente nela.
*/
void excluiUltimo(NO** lista) {
    NO* aux = NULL;
    NO* ultimo = NULL;

    if (*lista && (*lista)->prox) {
        aux = *lista;
        while (aux) { // Lista é percorrida
            if (!aux->prox->prox) break;
            aux = aux->prox;
        }
        ultimo = aux->prox; // Último elemento encontrado
        aux->prox = NULL;
        free(ultimo);
    }
    else if (*lista) *lista = NULL; // Exclui o único nó presente
}

/*
Função auxiliar que recebe uma lista e a distância máxima,
verificando se o caminho dado ultrapassa ou não a distância
permitida. Retorna true ou false conforme o caso.
*/
bool distanciaOk(NO** lista, int distanciaMaxima) {
    int d = 0;
    NO* p = *lista;
    while(p) {
        d++;
        p = p->prox;
    }
    return((d-1) <= distanciaMaxima); // Distância em arestas
}

/*
Função auxiliar que verifica se o vértice inicial ou final foi
atingido. No caso do vértice inicial, é inserido ao final da
lista atual (a qual representa o caminho atual). No caso do vértice
final, temos um caminho finalizado, restando verificar se sua
distância não ultrapassa a permitida e inseri-lo ao final da lista
contendo a resposta.
*/
void trataInicioOuFim(NO** listaAtual, NO** listaFinal, int d, int i, int x, int y) {
    if (i == x) // Vértice inicial atingido
        inserirElem(listaAtual, i); // Inserção do vértice inicial na lista

    if(i == y) // Vértice final atingido
        // Caso a condição for satisfeita (a distância não ultrapassa a permitida),
        // a lista atual é inserida ao final da lista final.
        if (distanciaOk(listaAtual,d))
            concatenaLista(listaFinal,listaAtual);
}

/*
Função principal responsável pela resolução do problema. Dados os vértices
de início e fim, obterá todos os caminhos possíveis entre eles e, ao chegar
no destino, verificará se o caminho satisfaz a distância dada.
*/
void buscaTodosOsCaminhos(VERTICE* g, int flag[], NO** listaAtual, NO** listaFinal, int d, int i, int x, int y) {
    flag[i] = 1; // Visitado

    trataInicioOuFim(listaAtual,listaFinal,d,i,x,y); // Vértice inicial ou final atingido

    NO* adj = g[i].inicio;

    while(adj) { // Lista de adjacências do vértice i é percorrida

        if(flag[adj->v] == 0) { // Não visitado
            inserirElem(listaAtual,adj->v); // Inserção ao final da lista
            buscaTodosOsCaminhos(g,flag,listaAtual,listaFinal,d,adj->v,x,y); // Percorre em profundidade
            excluiUltimo(listaAtual); // Ação desfeita (excluído do final da lista)
        }
        adj = adj->prox;

    }

    flag[i] = 0; // Ação desfeita para que outros caminhos passem pelo vértice i
}

//------------------------------------------
// O EP consiste em implementar esta funcao
// e outras funcoes auxiliares que esta
// necessitar
//------------------------------------------
NO* caminhos_max_d(VERTICE* g, int n, int x, int y, int d)
{
    if(!g) return NULL; // Grafo não existe

	NO* listaAtual = NULL; // Lista gerada durante o caminho atual
	NO* listaFinal = NULL; // Lista contendo todos os caminhos

    // Criação e inicialização do vetor de flags com 0
	int flag[n+1];
	for (int i=0; i<=n; i++) flag[i] = 0;

    /*
    Caso x e y não ultrapassem o número de vértices,
    a função principal é chamada e listaFinal conterá todos
    os caminhos possíveis para o problema. Se não existir
    nenhum caminho entre dois vértices, listaFinal conterá
    NULL.
    */
    if (x >= 0 && x <= n && y >= 0 && y <= n)
        buscaTodosOsCaminhos(g,flag,&listaAtual,&listaFinal,d,x,x,y);

	return listaFinal;
}
