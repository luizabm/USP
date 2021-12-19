#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

//-------------------------------------------

// CHLINK eh um par <chave,link> - dentro de cada página há 3 CHLINKs
typedef struct {
	int chave;
	int linkdir;
} CHLINK;

// definicao de pagina da árvore / registro do arquivo
typedef struct {
	int np; // armazene aqui o nro da pagina no arquivo
	int cont; // armazene aqui a quantidade de chaves existentes no vetor CHLINK[]
	CHLINK item[3]; // a chave[0] eh desprezada, e o linkdir[0] eh na verdade o link esquerdo da chave[1]
} PAGINA;


// funcao principal
void inserir(char nomearq[], int* raiz, int ch);

/*
Função chamada quando a árvore não existe, ou seja, quando o campo raiz contiver
o valor -1. A página da raiz é criada, a chave passada por parâmetro é inserida
e os campos da página são inicializados. Se a inserção foi bem sucedida, a função
retorna true. Caso contrário, retorna false.
*/
bool criaRaiz(char nomearq[], int* raiz, int ch) {
	// Abertura do arquivo no modo de escrita
	FILE* arq = fopen(nomearq,"wb");
	if (!arq) return false;

	// Criação da nova página
	PAGINA nova;
	nova.np = 0;
	nova.cont = 1;
	nova.item[0].chave = -1; // Inválida
	nova.item[0].linkdir = -1; // Folha
	nova.item[1].chave = ch; // Chave a ser inserida
	nova.item[1].linkdir = -1; // Folha
	nova.item[2].chave = -1; // Não existe
	nova.item[2].linkdir = -1; // Folha
	*raiz = nova.np; // Atualização do campo raiz

	// Escrita na primeira posição do arquivo
	fseek(arq, 0, SEEK_SET);
	int i = fwrite(&nova,sizeof(PAGINA),1,arq);
	fclose(arq);

	if (i == 1) return true;
	return false;
}

// Função que recebe o arquivo e o número da página a ser lida, retornando-a.
PAGINA lePaginaNoArquivo(FILE* arq, int numeroDaPagina) {
	PAGINA p;
	fseek(arq,numeroDaPagina * sizeof(PAGINA),SEEK_SET);
	fread(&p,sizeof(PAGINA),1,arq);
	return p;
}

/*
Função que verifica se dada página é uma folha ou não, retornando true ou false
conforme o caso.
*/
bool folha(PAGINA p) {
	return (p.item[0].linkdir == -1 && p.item[1].linkdir == -1 && p.item[2].linkdir == -1);
}

/*
Função que verifica se dada página está cheia (contém 2 chaves) ou não, retornando
true ou false conforme o caso.
*/
bool paginaCheia(PAGINA p) {
	return (p.cont == 2);
}

// Função que recebe o nome do arquivo e retorna o número de páginas escritas nele.
int nPaginasArq(char nomearq[]) {
	// Abertura do arquivo no modo de leitura
	FILE* arq = fopen(nomearq,"rb");

	PAGINA aux;
	int contador = 0;

	// Leitura de uma página por vez
	while(fread(&aux,sizeof(PAGINA),1,arq) == 1)
		contador++;

	return contador;
}

/*
Função que busca por uma chave ch no arquivo arq. Caso esteja inserida, a variável
booleana jaInserido é atualizada por referência com true. O valor retornado
corresponde à posição no vetor da página em que a chave está inserida, ou a 
posição em que deveria estar inserida.
*/
int buscaNaArvore(FILE* arq, PAGINA atual, int ch, bool* jaInserido) {
	int pos = 1; // Primeira chave válida na página

	while(ch > atual.item[pos].chave && pos < atual.cont) pos++;

	if (ch == atual.item[pos].chave) { // Valor já inserido
		*jaInserido = true;
		return pos;
	}

	if (folha(atual)) { // Atingiu-se uma página folha e ch não foi encontrada
		*jaInserido = false;
		if (ch > atual.item[pos].chave) return pos+1;
		return pos;
	}

	else { // A busca continua recursivamente
		PAGINA aux;

		if (ch > atual.item[pos].chave) // Pela direita
			aux = lePaginaNoArquivo(arq,atual.item[pos].linkdir);

		if (ch < atual.item[pos].chave) // Pela esquerda
			aux = lePaginaNoArquivo(arq,atual.item[pos-1].linkdir);

		buscaNaArvore(arq,aux,ch,jaInserido);
	}
}

/*
Função que busca por uma chave em determinada página. O valor retornado corresponde 
à posição no vetor da página em que a chave deveria estar inserida.
*/
int buscaNaPagina(PAGINA atual, int ch) {
	int pos = 1; // Primeira chave válida na página
	while(ch > atual.item[pos].chave && pos < atual.cont) pos++;
	return pos;
}

/*
Função que insere uma chave (e seu link) em uma página não cheia. A página pode ser
ajustada, caso necessário, a fim de manter sua ordenação.
*/
bool insereNaPagina(char nomearq[], PAGINA* atual, CHLINK ch) { 
	// Abertura do arquivo no modo leitura + escrita
	FILE* arq = fopen(nomearq,"r+b");

	int n = atual->cont; // Número de chaves presentes na página atual
	int chave = ch.chave; // Chave a ser inserida

	if (n == 0) // Página vazia
		(*atual).item[n+1] = ch;

	// Swap necessário a fim de manter ordenação
	else if ((*atual).item[n].chave > chave) {
		CHLINK aux = (*atual).item[n];
		(*atual).item[n] = ch;
		(*atual).item[n+1] = aux;
	}

	else // Apenas inserir já garantirá ordenação
		(*atual).item[n+1] = ch;

	(*atual).cont++;

	// Escrita na posição da página no arquivo
	fseek(arq,(*atual).np * sizeof(PAGINA), SEEK_SET);
	int i = fwrite(atual,sizeof(PAGINA),1,arq);
	fclose(arq);

	if (i == 1) return true;
	return false;
}

/*
Função que ordena um vetor com 3 elementos do tipo CHLINK de acordo com o valor das
chaves. Utiliza, para isso, o Bubble Sort. É necessária para a função de split.
*/
void ordenaVetor(CHLINK v[]) {
	for (int i = 2; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			if (v[j].chave > v[j+1].chave) {
				CHLINK aux = v[j];
				v[j] = v[j+1];
				v[j+1] = aux;
			}
		}
	}
}

/*
Método que recebe uma página, a chave a ser inserida (com seu link) e o vetor
que conterá todas as chaves e seus links. Insere no vetor as 3 chaves presentes
e o ordena.
*/
void preencheVetorOrdenado(PAGINA atual, CHLINK* ch, CHLINK todasAsChaves[]) {
	// Chave a ser inserida é colocada na posição 0
	todasAsChaves[0].chave = ch->chave;
	todasAsChaves[0].linkdir = ch->linkdir;

	// Duas chaves já presentes na página colocadas em 1 e 2
	for (int i = 1; i < 3; i++) {
		todasAsChaves[i].chave = atual.item[i].chave;
		todasAsChaves[i].linkdir = atual.item[i].linkdir;
	}

	ordenaVetor(todasAsChaves); // Ordenação do vetor
}

/*
Função que realiza split em uma página do arquivo. A página passada por parâmetro
ficará à esquerda e uma nova página será criada para ficar à direita. O elemento
central é promovido para o nível superior e inserido recursivamente posteriormente,
tratando-se do separador das páginas esquerda e direita.
O caso especial em que a raiz sofrerá split também é tratado.
*/
void splitNaPagina(char nomearq[], PAGINA atual, CHLINK* ch, int* nPaginas, int* raiz, int* flag) {
	// Abertura do arquivo no modo leitura + escrita
	FILE* arq = fopen(nomearq,"r+b");

	// Vetor contendo as 3 chaves é ordenado
	CHLINK todasAsChaves[3];
	preencheVetorOrdenado(atual,ch,todasAsChaves);

	// Página atual (filha esquerda do separador)
	atual.cont--;
	atual.item[1] = todasAsChaves[0]; // Menor chave
	atual.item[2].chave = -1; // Não existe
	atual.item[2].linkdir = -1;
	fseek(arq,atual.np * sizeof(PAGINA), SEEK_SET);
	fwrite(&atual,sizeof(PAGINA),1,arq);

	// Nova página (filha direita do separador)
	PAGINA nova;
	if (*raiz == atual.np) nova.np = (*nPaginas)+1; // Caso especial
	else nova.np = (*nPaginas);
	nova.cont = 1;
	nova.item[0].chave = -1; // Inválida
	nova.item[0].linkdir = todasAsChaves[1].linkdir; 
	nova.item[1].chave = todasAsChaves[2].chave; // Maior chave
	nova.item[1].linkdir = todasAsChaves[2].linkdir;
	nova.item[2].chave = -1; // Não existe
	nova.item[2].linkdir = -1;
	fseek(arq,nova.np * sizeof(PAGINA), SEEK_SET);
	fwrite(&nova,sizeof(PAGINA),1,arq);

	// Chave promovida
	CHLINK chavePromovida;
	chavePromovida.chave = todasAsChaves[1].chave; // Chave mediana
	chavePromovida.linkdir = nova.np; 
	*ch = chavePromovida; // A chave promovida deve ser inserida recursivamente

	// Caso especial (criação da nova raiz)
	if (*raiz == atual.np) {
		PAGINA novaRaiz;
		novaRaiz.np = (*nPaginas);
		novaRaiz.cont = 1;
		novaRaiz.item[0].chave = -1; // Inválida
		novaRaiz.item[0].linkdir = atual.np; // Conecta à esquerda
		novaRaiz.item[1].chave = chavePromovida.chave; // Chave promovida
		novaRaiz.item[1].linkdir = nova.np; // Conecta à direita
		novaRaiz.item[2].chave = -1; // Não existe
		novaRaiz.item[2].linkdir = -1; 
		fseek(arq,novaRaiz.np * sizeof(PAGINA), SEEK_SET);
		fwrite(&novaRaiz,sizeof(PAGINA),1,arq);

		(*raiz) = novaRaiz.np; // Atualização da raiz
		(*flag) = 0; // Não há necessidade de inserir a chave promovida na recursão
		(*nPaginas)++;
	}

	(*nPaginas)++;

	fclose(arq);
}

/*
Função que insere a chave na página atual de acordo com o caso. Para isso, verifica
se a página está cheia, caso em que o split precisa ser realizado; ou não, caso em
que a chave pode ser inserida diretamente na página atual.
*/
void insereConformeCaso(char nomearq[], PAGINA atual, CHLINK* ch, int* nPaginas, int* raiz, int* flag) {
	if (paginaCheia(atual)) {
		*flag = 1; // Ocorreu overflow
		splitNaPagina(nomearq,atual,ch,nPaginas,raiz,flag);
	}

	else {
		*flag = 0; // Não ocorreu overflow
		insereNaPagina(nomearq,&atual,*ch);
	}
}

/*
Método principal que insere a chave na árvore recursivamente, verificando também se
os níveis superiores foram afetados pela inserção. Caso tenham sido, outras inserções
são feitas.
*/
void insereR(char nomearq[], FILE* arq, PAGINA atual, CHLINK* ch, int* nPaginas, int* raiz, int* flag) {
	// Busca da posição no vetor em que a chave deveria estar
	int pos = buscaNaPagina(atual,(*ch).chave);

	if (folha(atual))  // Atingiu-se a folha e pode-se realizar a inserção da chave desejada
		insereConformeCaso(nomearq,atual,ch,nPaginas,raiz,flag);
	
	else { // Descida recursiva na árvore
		PAGINA aux;

		if ((*ch).chave > atual.item[pos].chave) // Pela direita
			aux = lePaginaNoArquivo(arq,atual.item[pos].linkdir);

		if ((*ch).chave < atual.item[pos].chave) // Pela esquerda
			aux = lePaginaNoArquivo(arq,atual.item[pos-1].linkdir);

		insereR(nomearq,arq,aux,ch,nPaginas,raiz,flag);

		// Após a descida, verifica-se se ocorreu overflow e, portanto, se outras chaves devem
		// ser inseridas
		if ((*flag) == 1) // Ocorreu overflow
			insereConformeCaso(nomearq,atual,ch,nPaginas,raiz,flag);
	}
}

//------------------------------------------
// O EP consiste em implementar esta funcao
// e outras funcoes auxiliares que esta
// necessitar
//------------------------------------------

void inserir(char nomearq[], int* raiz, int ch) {
	int nPaginas = 0;

	if (*raiz == -1) { // Arquivo não existe
		bool arqCriado = criaRaiz(nomearq,raiz,ch);
		if (!arqCriado) return;
		nPaginas = 1;
	}

	else {
		// Abertura do arquivo no modo leitura + escrita
		FILE* arq = fopen(nomearq,"r+b");

		// Obtenção do número de páginas já escritas
		nPaginas = nPaginasArq(nomearq);

		// Leitura da página contendo a raiz
		PAGINA pagRaiz = lePaginaNoArquivo(arq,*raiz);

		// Verificação se a chave já existe na árvore
		bool jaInserido = false;
		buscaNaArvore(arq,pagRaiz,ch,&jaInserido);
		if (jaInserido) return;

		// Elemento a ser inserido em folha
		CHLINK elemento;
		elemento.chave = ch;
		elemento.linkdir = -1;
		int flag = -1;

		// Inserção recursiva
		insereR(nomearq,arq,pagRaiz,&elemento,&nPaginas,raiz,&flag);

		fclose(arq);
	}
}