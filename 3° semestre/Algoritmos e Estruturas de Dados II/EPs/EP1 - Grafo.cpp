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
Fun��o auxiliar que recebe uma lista, representada por seu
n� inicial, e um v�rtice, inserindo-o ao final da lista
ligada.
*/
void inserirElem(NO** lista, int vertice) {

    // Cria��o do novo n� a ser inserido
    NO* novo = (NO*) malloc(sizeof(NO));
    novo->v = vertice;
    novo->prox = NULL;

    NO* aux = NULL;

    // J� existem elementos na lista
    if (*lista) {
        aux = *lista;
        while (aux) {
            if (!aux->prox) break;
            aux = aux->prox;
        }
        aux->prox = novo; // Inser��o ao final
    }
    else *lista = novo; // Lista era vazia
}

/*
Fun��o auxiliar que recebe uma lista principal, uma
outra lista, e insere a segunda ao final da lista
principal. Para isso, utiliza a fun��o inserirElem.
*/
void concatenaLista(NO** listaPrincipal, NO** lista) {
    NO* p = *lista;
    while(p) {
        inserirElem(listaPrincipal, p->v);
        p = p->prox;
    }
}

/*
Fun��o auxiliar que recebe uma lista e exclui o
�ltimo elemento presente nela.
*/
void excluiUltimo(NO** lista) {
    NO* aux = NULL;
    NO* ultimo = NULL;

    if (*lista && (*lista)->prox) {
        aux = *lista;
        while (aux) { // Lista � percorrida
            if (!aux->prox->prox) break;
            aux = aux->prox;
        }
        ultimo = aux->prox; // �ltimo elemento encontrado
        aux->prox = NULL;
        free(ultimo);
    }
    else if (*lista) *lista = NULL; // Exclui o �nico n� presente
}

/*
Fun��o auxiliar que recebe uma lista e a dist�ncia m�xima,
verificando se o caminho dado ultrapassa ou n�o a dist�ncia
permitida. Retorna true ou false conforme o caso.
*/
bool distanciaOk(NO** lista, int distanciaMaxima) {
    int d = 0;
    NO* p = *lista;
    while(p) {
        d++;
        p = p->prox;
    }
    return((d-1) <= distanciaMaxima); // Dist�ncia em arestas
}

/*
Fun��o auxiliar que verifica se o v�rtice inicial ou final foi
atingido. No caso do v�rtice inicial, � inserido ao final da
lista atual (a qual representa o caminho atual). No caso do v�rtice
final, temos um caminho finalizado, restando verificar se sua
dist�ncia n�o ultrapassa a permitida e inseri-lo ao final da lista
contendo a resposta.
*/
void trataInicioOuFim(NO** listaAtual, NO** listaFinal, int d, int i, int x, int y) {
    if (i == x) // V�rtice inicial atingido
        inserirElem(listaAtual, i); // Inser��o do v�rtice inicial na lista

    if(i == y) // V�rtice final atingido
        // Caso a condi��o for satisfeita (a dist�ncia n�o ultrapassa a permitida),
        // a lista atual � inserida ao final da lista final.
        if (distanciaOk(listaAtual,d))
            concatenaLista(listaFinal,listaAtual);
}

/*
Fun��o principal respons�vel pela resolu��o do problema. Dados os v�rtices
de in�cio e fim, obter� todos os caminhos poss�veis entre eles e, ao chegar
no destino, verificar� se o caminho satisfaz a dist�ncia dada.
*/
void buscaTodosOsCaminhos(VERTICE* g, int flag[], NO** listaAtual, NO** listaFinal, int d, int i, int x, int y) {
    flag[i] = 1; // Visitado

    trataInicioOuFim(listaAtual,listaFinal,d,i,x,y); // V�rtice inicial ou final atingido

    NO* adj = g[i].inicio;

    while(adj) { // Lista de adjac�ncias do v�rtice i � percorrida

        if(flag[adj->v] == 0) { // N�o visitado
            inserirElem(listaAtual,adj->v); // Inser��o ao final da lista
            buscaTodosOsCaminhos(g,flag,listaAtual,listaFinal,d,adj->v,x,y); // Percorre em profundidade
            excluiUltimo(listaAtual); // A��o desfeita (exclu�do do final da lista)
        }
        adj = adj->prox;

    }

    flag[i] = 0; // A��o desfeita para que outros caminhos passem pelo v�rtice i
}

//------------------------------------------
// O EP consiste em implementar esta funcao
// e outras funcoes auxiliares que esta
// necessitar
//------------------------------------------
NO* caminhos_max_d(VERTICE* g, int n, int x, int y, int d)
{
    if(!g) return NULL; // Grafo n�o existe

	NO* listaAtual = NULL; // Lista gerada durante o caminho atual
	NO* listaFinal = NULL; // Lista contendo todos os caminhos

    // Cria��o e inicializa��o do vetor de flags com 0
	int flag[n+1];
	for (int i=0; i<=n; i++) flag[i] = 0;

    /*
    Caso x e y n�o ultrapassem o n�mero de v�rtices,
    a fun��o principal � chamada e listaFinal conter� todos
    os caminhos poss�veis para o problema. Se n�o existir
    nenhum caminho entre dois v�rtices, listaFinal conter�
    NULL.
    */
    if (x >= 0 && x <= n && y >= 0 && y <= n)
        buscaTodosOsCaminhos(g,flag,&listaAtual,&listaFinal,d,x,x,y);

	return listaFinal;
}
