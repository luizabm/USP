#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <malloc.h>
#include <cstring>

// Elemento da pilha
typedef struct estrutura {
	struct estrutura *prox;
       	int tipo; // 1=char e 2=float
       	union {
              	char simbolo;
              	float valor;
       	};
} NO;

// Definição da pilha, estrutura auxiliar utilizada
typedef struct {
    NO* topo;
} PDINAM;

// Função principal (retorna float e int)
float calcular(char* expressao, int* codigo);

/*
Função PUSH que insere os caracteres da expressão no
topo da pilha, definindo seus tipos (sendo 1 para char
e 2 para float), preenchendo a informação do campo
union de acordo com o tipo.
*/
void push(char caracter, PDINAM* p) {
    NO* novo = (NO*) malloc(sizeof(NO));
    int tipo;
    if (caracter == '(' || caracter == ')') tipo = 1;
    else if (caracter == '+' || caracter == '-') tipo = 1;
    else if (caracter == '*' || caracter == '/') tipo = 1;
    else tipo = 2;

    novo->tipo = tipo; // 1=char e 2=float
    if (novo->tipo == 1) novo->simbolo = caracter;
    if (novo->tipo == 2) {
        novo->valor = (float) caracter-48;
    }

    novo->prox = p->topo;
    p->topo = novo;
}

/*
Função PUSH que insere um valor float no topo da pilha.
Utilizada para inserir na pilha os resultados parciais
obtidos nos parênteses.
*/
void pushValor(float valor, PDINAM* p) {
    NO* novo = (NO*) malloc(sizeof(NO));
    novo->tipo = 2; // 1=char e 2=float
    novo->valor = valor;
    novo->prox = p->topo;
    p->topo = novo;
}

/*
Função POP que retira o nó do topo da pilha. Se a
retirada for bem sucedida, a função retorna o tipo
do nó. Senão, retorna -1, indicando que a pilha
estava vazia.
*/
int pop(PDINAM* p) {
    NO* aux;
    int apagar;
    if(!p->topo) return -1;
    aux = p->topo;
    apagar = aux->tipo;
    p->topo = p->topo->prox;
    free(aux);
    return(apagar);
}

/*
Função auxiliar que calcula um resultado parcial.
Recebe dois floats, um char representando a operação
a ser realizada e o código (por referência), para o
caso em que uma divisão por zero é realizada.
*/
float resultado(float x, float y, char operador, int* codigo) {
    switch (operador) {
        case '-': return x-y;
        case '+': return x+y;
        case '*': return x*y;
        case '/':
            if (y == 0) {
                *codigo = 0;
                return -1; // Indicador de erro
            }
            return x/y;
        default:
            return 0;
    }
}

/*
Função auxiliar que indica erro. Será utilizada para
identificar os casos em que números e operadores/
parênteses não estão na ordem em que deveriam, sendo
necessário, portanto, retornar -1 como código.
*/
int verificaErro(PDINAM* pilha, int tipo, int* codigo) {
    if(pilha->topo->tipo == tipo) {
        if (*codigo != 0) *codigo = -1;
        return -1;
    }
    return 1;
}

/*
Função auxiliar que resolve o parênteses completo após
encontrar um fechamento de parênteses, calculando o
resultado parcial da operação utilizando as funções
auxiliares - para cálculo e verificação de erro.
*/
void resolveParenteses(PDINAM* pilha, int* codigo) {
    if (verificaErro(pilha,1,codigo) == -1) return;
    float b = pilha->topo->valor;
    pop(pilha);

    if (verificaErro(pilha,2,codigo) == -1) return;
    char operador = pilha->topo->simbolo;
    pop(pilha);

    if (verificaErro(pilha,1,codigo) == -1) return;
    float a = pilha->topo->valor;
    pop(pilha);

    float aux = resultado(a,b,operador,codigo);
    if (pilha->topo) pop(pilha);
    else *codigo = -1;
    pushValor(aux,pilha);
}

//------------------------------------------
// O EP consiste em implementar esta funcao
// e outras funcoes auxiliares que esta
// necessitar
//------------------------------------------
float calcular(char* expressao, int* codigo){

	float resp = 0.0;
	*codigo = 999;

	PDINAM* pilha = (PDINAM*) malloc(sizeof(PDINAM));
	pilha->topo = NULL;

    int i = 0;
	while(expressao[i]) {
        if (expressao[i] != ')') push(expressao[i],pilha);

        if (expressao[i] == ')') resolveParenteses(pilha,codigo);
        if (*codigo == -1 || *codigo == 0) break;
        i++;
	}

	if (pilha->topo->tipo == 2 && *codigo != 0 && *codigo != -1) {
        resp = pilha->topo->valor;
        pop(pilha);
        if (pilha->topo == NULL) *codigo = 1;
        else *codigo = -1;
    }

	return resp;
}



//----------------------------------------------------------------
// use main() apenas para fazer chamadas de teste ao seu programa
//----------------------------------------------------------------
int main() {


	// o EP sera testado com chamadas deste tipo

	char exp[200];
	strcpy(exp, "(7*5)");

	int codigo;

	float resp = calcular(exp,&codigo);
	printf("%f \n",resp);

    /*
    ((7*5)/(9-2)) 1 5
2 (5/(7-3)*5 -1
3 ((((2*3)/0)*(3+5)-1)-9) 0
4 ((1+5)+((3*2)+4)) 1 16
5 ((3*5)-((7+(4*5))*(6/6))) 1 -12
6 (0*((((8+(2-4))/6)-5)*6)) 1 0
7 5*1)-9)*(2/2)-1)-9) -1
8 ((((((((((2*3)+5)*3)-1)-9)+6)/2)*4)/5)-5) 1 6,6
9 ((3+5)*((((3*4)-8)/2)+1)) 1 24
10 0 -1

    */

    strcpy(exp, "((7*5)/(9-2))");
	float resultado = calcular(exp, &codigo);
	printf("Testando ((7*5)/(9-2)):\n");
	if(codigo!= 1) printf("Codigo retornado errado, tá dando %d \n",codigo);
	if(resultado != 5) printf("Resultado errado\n");
	if(codigo == 1 && resultado == 5) printf("deu certo\n");
    printf("\n");


    strcpy(exp, "(5/(7-3)*5");
	resultado = calcular(exp, &codigo);
	printf("Testando (5/(7-3)*5:\n");
	if(codigo!= -1) printf("Codigo retornado errado, tá dando %d \n",codigo);
	if(codigo == -1 ) printf("deu certo\n");
	exp[200] = NULL;
	printf("\n");

    /*
    strcpy(exp, "(0*((1+(2*4)/6)))");
	resultado = calcular(exp, &codigo);
	printf("Testando (0*((1+(2*4)/6))):\n");
	if(codigo!= 1) printf("Codigo retornado errado, tá dando %d \n",codigo);
	if(resultado != 0) printf("Resultado errado\n");
	if(codigo == 1 && resultado == 0) printf("deu certo\n");
    printf("\n");
    */

    exp[200] = NULL;
    strcpy(exp, "((((2*3)/0)*(3+5)-1)-9)");
	resultado = calcular(exp, &codigo);
	printf("Testando ((((2*3)/0)*(3+5)-1)-9):\n");
	if(codigo!= 0) printf("Codigo retornado errado, tá dando %d \n",codigo);
	if(codigo == 0 ) printf("deu certo\n");
    exp[200] = NULL;
    printf("\n");

    exp[200] = NULL;
    strcpy(exp, "((1+5)+((3*2)+4))");
	resultado = calcular(exp, &codigo);
	printf("Testando ((1+5)+((3*2)+4)):\n");
	if(codigo!= 1) printf("Codigo retornado errado, tá dando %d \n",codigo);
	if(resultado != 16) printf("Resultado errado, tá dando %f \n",resultado);
	if(codigo == 1 && resultado == 16) printf("deu certo\n");
    exp[200] = NULL;
    printf("\n");

    exp[200] = NULL;
    strcpy(exp, "((3*5)-((7+(4*5))*(6/6)))");
	resultado = calcular(exp, &codigo);
	printf("Testando : ((3*5)-((7+(4*5))*(6/6))) \n");
	if(codigo!= 1) printf("Codigo retornado errado, tá dando %d \n",codigo);
	if(resultado != -12) printf("Resultado errado, tá dando %f \n",resultado);
	if(codigo == 1 && resultado == -12) printf("deu certo\n");
    exp[200] = NULL;
    printf("\n");

    exp[200] = NULL;
    strcpy(exp, "(0*((((8+(2-4))/6)-5)*6))");
	resultado = calcular(exp, &codigo);
	printf("Testando : (0*((((8+(2-4))/6)-5)*6)) \n");
	if(codigo!= 1) printf("Codigo retornado errado, tá dando %d \n",codigo);
	if(resultado != 0) printf("Resultado errado, tá dando %f \n",resultado);
	if(codigo == 1 && resultado == 0) printf("deu certo\n");
    exp[200] = NULL;
    printf("\n");

    exp[200] = NULL;
    strcpy(exp, "5*1)-9)*(2/2)-1)-9)");
	resultado = calcular(exp, &codigo);
	printf("Testando 5*1)-9)*(2/2)-1)-9):\n");
	if(codigo!= -1) printf("Codigo retornado errado, tá dando %d \n",codigo);
	if(codigo == -1 ) printf("deu certo\n");
    exp[200] = NULL;
    printf("\n");

    exp[200] = NULL;
    strcpy(exp, "((((((((((2*3)+5)*3)-1)-9)+6)/2)*4)/5)-5)");
	resultado = calcular(exp, &codigo);
	printf("Testando ((((((((((2*3)+5)*3)-1)-9)+6)/2)*4)/5)-5) :\n");
	if(codigo!= 1) printf("Codigo retornado errado, tá dando %d \n",codigo);
	if(resultado != 6.6) printf("Resultado errado, tá dando %f \n",resultado);
	if(codigo == 1 && resultado == 6.6) printf("deu certo\n");
    exp[200] = NULL;
    printf("\n");

    exp[200] = NULL;
    strcpy(exp, "((3+5)*((((3*4)-8)/2)+1))");
	resultado = calcular(exp, &codigo);
	printf("Testando ((3+5)*((((3*4)-8)/2)+1)):\n");
	if(codigo!= 1) printf("Codigo retornado errado, tá dando %d \n",codigo);
	if(resultado != 24) printf("Resultado errado, tá dando %f \n",resultado);
	if(codigo == 1 && resultado == 24) printf("deu certo\n");
    exp[200] = NULL;
    printf("\n");

    exp[200] = NULL;
    strcpy(exp, "0");
	resultado = calcular(exp, &codigo);
	printf("Testando 0:\n");
	if(codigo!= -1) printf("Codigo retornado errado, tá dando %d \n",codigo);
	if(codigo == -1 ) printf("deu certo\n");
    exp[200] = NULL;
    printf("\n");
}

// por favor nao inclua nenhum código abaixo da função main()
