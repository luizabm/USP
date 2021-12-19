#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

// no da arvore
typedef struct estr {
        int chave;
        struct estr *esq;
	struct estr *dir;
} NO;

void organizar(NO* *raiz);


// Método auxiliar para encontrar o endereço do pai da chave procurada
void travessiap(NO* p, int ch, NO* *no_pai, bool *achou) {
    if(p) {
        if(p->esq)
            if(p->esq->chave == ch) {
                *achou = true;
                *no_pai = p;
            }
        if(!*achou)
            if(p->dir)
                if(p->dir->chave == ch) {
                    *achou = true;
                    *no_pai = p;
                }
        if(!*achou)
            travessiap(p->esq, ch, no_pai, achou);
        if(!*achou)
            travessiap(p->dir, ch, no_pai, achou);
    }
}

// Retorna o endereço do pai da chave procurada
NO* encontraPai(NO* raiz, int ch) {
    bool achou = false;
    NO* no_pai;
    if(raiz) {
        if(raiz->chave == ch)
            return(NULL);
        else {
            travessiap(raiz, ch, &no_pai, &achou);
            return(no_pai);
        }
    }
}

// Retorna o nó com a menor chave na árvore
NO* menorChave(NO* p) {
    NO* menor = p;
    if (p->esq) {
        NO* menorEsq = menorChave(p->esq);
        if (menorEsq->chave < menor->chave) menor = menorEsq;
    }

    if (p->dir) {
        NO* menorDir = menorChave(p->dir);
        if (menorDir->chave < menor->chave) menor = menorDir;
    }

    return menor;
}

// Retorna o nó com a maior chave na árvore
NO* maiorChave(NO* p) {
    NO* maior = p;
    if (p->esq) {
        NO* maiorEsq = maiorChave(p->esq);
        if (maiorEsq->chave > maior->chave) maior = maiorEsq;
    }

    if (p->dir) {
        NO* maiorDir = maiorChave(p->dir);
        if (maiorDir->chave > maior->chave) maior = maiorDir;
    }

    return maior;
}

// Retorna o número de chaves na árvore
int numChaves (NO* raiz) {
    if (raiz)
        return (1 + numChaves(raiz->esq) + numChaves(raiz->dir));

    return 0;
}

/*
Verifica se uma dada árvore é ABB. Se não for, retorna por referência
o endereço do nó na posição errada na árvore.
*/
bool verificaABB (NO* raiz, NO** foraDeOrdem) {
    if (!raiz) return true; // vazia é ABB

    int ch = raiz->chave;

    // Problemas nas subárvores
    if (raiz->esq && maiorChave(raiz->esq)->chave > ch) {
        *foraDeOrdem = maiorChave(raiz->esq);
        return false;
    }

    if (raiz->dir && menorChave(raiz->dir)->chave < ch) {
        *foraDeOrdem = menorChave(raiz->dir);
        return false;
    }

    // Chamadas recursivas
    if (!verificaABB(raiz->esq,foraDeOrdem) || !verificaABB(raiz->dir,foraDeOrdem))
        return false;

    return true;
}

/*
Método auxiliar que sobrescreve o elemento errado caso ele seja, na realidade,
a raiz da árvore.
*/
void identificaErrado (NO* raiz, NO** foraDeOrdem) {
    if (!verificaABB(raiz,foraDeOrdem)) {
        int ch = raiz->chave;

        if (numChaves(raiz->esq) == 1 && ch < raiz->esq->chave)
            *foraDeOrdem = raiz->esq;

        else if (numChaves(raiz->dir) == 1 && ch > raiz->dir->chave)
            *foraDeOrdem = raiz->dir;

        else if (raiz->esq && raiz->dir && ch > maiorChave(raiz->esq)->chave && ch > maiorChave(raiz->dir)->chave)
            *foraDeOrdem = raiz;

        else if (raiz->esq && raiz->dir && ch < menorChave(raiz->esq)->chave && ch < menorChave(raiz->dir)->chave)
            *foraDeOrdem = raiz;

        else if (raiz->esq && raiz->dir && ch > maiorChave(raiz->esq)->chave && ch > menorChave(raiz->dir)->chave && verificaABB(raiz->dir,foraDeOrdem) && verificaABB(raiz->esq,foraDeOrdem))
            *foraDeOrdem = raiz;

        else if (raiz->esq && raiz->dir && ch < menorChave(raiz->dir)->chave && ch < maiorChave(raiz->esq)->chave && verificaABB(raiz->dir,foraDeOrdem) && verificaABB(raiz->esq,foraDeOrdem))
            *foraDeOrdem = raiz;

        else if (raiz->esq && !(raiz->dir) && ch < maiorChave(raiz->esq)->chave && verificaABB(raiz->esq,foraDeOrdem))
            *foraDeOrdem = raiz;

        else if (!(raiz->esq) && raiz->dir && ch > menorChave(raiz->dir)->chave && verificaABB(raiz->dir,foraDeOrdem))
            *foraDeOrdem = raiz;

        else if (raiz->esq && ch < raiz->esq->chave)
            *foraDeOrdem = raiz->esq;

        else if (raiz->dir && ch > raiz->dir->chave)
            *foraDeOrdem = raiz->dir;
    }
}

// Deleta o nó errado na árvore.
void deletaNo(NO* raiz, NO* foraDeOrdem) {
    NO* p = raiz;
    NO* pai = NULL;
    NO* filho = NULL;

    pai = encontraPai(p,foraDeOrdem->chave);

    // Exclusão em folha
    if (!(foraDeOrdem->dir) && !(foraDeOrdem->esq)) {
        if (pai->esq && foraDeOrdem == pai->esq) {
            filho = pai->esq;
            pai->esq = NULL;
            free(filho);
        }

        else if (pai->dir && pai->dir == foraDeOrdem) {
            filho = pai->dir;
            pai->dir = NULL;
            free(filho);
        }
        return;
    }

    // Possui apenas o filho direito.
    if (foraDeOrdem->dir && !(foraDeOrdem->esq)) {
        filho = foraDeOrdem->dir;

        if (foraDeOrdem == pai->esq)
            pai->esq = filho;

        if (pai->dir == foraDeOrdem)
            pai->dir = filho;
        free(foraDeOrdem);
        return;
    }

    // Possui apenas o filho esquerdo.
    if (!(foraDeOrdem->dir) && foraDeOrdem->esq) {
        filho = foraDeOrdem->esq;
        if (pai->esq == foraDeOrdem)
            pai->esq = filho;

        if (pai->dir == foraDeOrdem)
            pai->dir = filho;

        free(foraDeOrdem);
        return;
    }

    // Possui 2 filhos.
    if (foraDeOrdem->dir && foraDeOrdem->esq) {

            NO* maiorEsquerda = maiorChave(foraDeOrdem->esq);
            int valor = maiorEsquerda->chave;

            // O substituto era folha
            if (!(maiorEsquerda->dir) && !(maiorEsquerda->esq)) {
                pai = encontraPai(p,maiorEsquerda->chave);
                if (pai->esq == maiorEsquerda) {
                    pai->esq = NULL;
                    free(maiorEsquerda);
                }
                if (pai->dir == maiorEsquerda) {
                    pai->dir = NULL;
                    free(maiorEsquerda);
                }
            }

            // O substituto tinha filho esquerdo
            if (!(maiorEsquerda->dir) && maiorEsquerda->esq) {
                pai = encontraPai(p,maiorEsquerda->chave);
                if (pai->esq == maiorEsquerda) {
                    pai->esq = maiorEsquerda->esq;
                    free(maiorEsquerda);
                }
                if (pai->dir == maiorEsquerda) {
                    pai->dir = maiorEsquerda->esq;
                    free(maiorEsquerda);
                }

            }
            foraDeOrdem->chave = valor;
    }
}

// Deleta o nó errado na árvore quando ele é a raiz.
void deletaRaiz(NO** raiz) {
    NO* p = *raiz;
    NO* pai = NULL;
    NO* filho = NULL;

    if (p->esq && p->dir) {
            // Exclusão com 2 filhos
            NO* maiorEsquerda = maiorChave(p->esq);
            int valor = maiorEsquerda->chave;

            // O substituto era folha
            if (!(maiorEsquerda->dir) && !(maiorEsquerda->esq)) {
                pai = encontraPai(p,maiorEsquerda->chave);
                if (pai->esq == maiorEsquerda) {
                    pai->esq = NULL;
                    free(maiorEsquerda);
                }
                if (pai->dir == maiorEsquerda) {
                    pai->dir = NULL;
                    free(maiorEsquerda);
                }
            }

            // O substituto tinha filho esquerdo
            if (!(maiorEsquerda->dir) && maiorEsquerda->esq) {
                pai = encontraPai(p,maiorEsquerda->chave);
                filho = maiorEsquerda->esq;
                if (pai->esq == maiorEsquerda)
                    pai->esq = filho;

                if (pai->dir == maiorEsquerda)
                    pai->dir = filho;

                free(maiorEsquerda);
            }

            (*raiz)->chave = valor;
        }

    else if (p->esq) {
        // Exclusão quando possui só o filho esquerdo
        *raiz = p->esq;
        free(p);
        return;
    }
    else if (p->dir) {
        // Exclusão quando possui só o filho direito
        *raiz = p->dir;
        free(p);
        return;
    }
}

//------------------------------------------
// O EP consiste em implementar esta funcao
//------------------------------------------
void organizar(NO* *raiz) {

    NO* p = *raiz;
    NO* foraDeOrdem = NULL;
    NO* pai = NULL;
    NO* filho = NULL;

    if (verificaABB(p,&foraDeOrdem)) return;

    verificaABB(p,&foraDeOrdem);
    identificaErrado(p,&foraDeOrdem);


    if (numChaves(p) == 2) {
        if (p->esq && p->esq->chave > p->chave) {
            // Excluir p->esq
            filho = p->esq;
            p->esq = NULL;
            free(filho);

        }
        if (p->dir && p->dir->chave < p->chave) {
            // Excluir p->dir
            filho = p->dir;
            p->dir = NULL;
            free(filho);
        }
    }

    // Raiz é o elemento fora de lugar
    if (p == foraDeOrdem) deletaRaiz(raiz);

    else deletaNo(p,foraDeOrdem);

}


//---------------------------------------------------------
// use main() para fazer chamadas de teste ao seu programa
//---------------------------------------------------------
int main() {

	NO* arv = NULL;


	return 0;

}

// por favor nao inclua nenhum código abaixo da função main()
