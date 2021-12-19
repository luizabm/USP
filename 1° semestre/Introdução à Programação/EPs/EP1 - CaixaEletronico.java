/**                Primeiro Exercício-Programa                      **/
/**   15/04/2020                                                    **/
/*********************************************************************/

/*
	Caixa eletrônico das Ilhas Weblands, com estoque ilimitado de cédulas
	de B$50,00, B$10,00, B$5,00 e B$1,00.
*/
public class CaixaEletronico {
	// Número de cédulas de B$50,00
	static int n50;
	
	// Número de cédulas de B$10,00
	static int n10;

	// Número de cédulas de B$5,00
	static int n5;
	
	// Número de cédulas de B$1,00
	static int n1;


	/*
		Determina a quantidade de cada nota necessária para totalizar
		um determinado valor de retirada, de modo a minimizar a quantidade
		de cédulas entregues.
		
		Abastece as variáveis globais n50, n10, n5 e n1 com seu respectivo
		número de cédulas.
		
		Parâmetro:
			valor - O valor a ser retirado
	*/
	static void fazRetirada(int valor) {
		/* 
		Inicialização das variáveis globais, correspondentes ao número
		de cédulas, com 0. 
		*/
		n50 = 0;
		n10 = 0;
		n5 = 0;
		n1 = 0;

		/*
		Caso o parâmetro valor receba um valor menor que 0, -1 será
		atribuído às variáveis.
		*/
		if (valor<0){
			n50 = -1;
			n10 = -1;
			n5 = -1;
			n1 = -1;
		}

		/* 
		Se o valor for positivo, o metódo calcula o número mínimo de
		cédulas a serem retiradas para completar o valor do saque.
		*/
		else {
			/*
			O número de notas de 50 é representado pela variável n50,
			e calculado pela divisão do valor do saque por 50. Como se
			trata de uma divisão inteira, haverá uma quantia exata de
			notas.
			Para as demais cédulas, desconta-se a quantia de dinheiro 
			correspondente a todas as notas, de maior valor, sacadas
			anteriormente - multiplicando o número de cédulas por seu 
			valor - e, em seguida, divide-se o resultado pelo valor da
			cédula em questão. Todas as variáveis conterão valores inteiros.
			*/
			n50 = valor/50;
			n10 = (valor - 50*n50)/10;
			n5 = (valor - 50*n50 - 10*n10)/5;
			n1 = (valor - 50*n50 - 10*n10 - 5*n5);
		}
	}
	
	/*
		Teste.
	*/
	public static void main(String[] args) {
		
		System.out.println("Saque \t Notas de 50 \t Notas de 10 \t Notas de 5 \t Notas de 1");
		int saque = -10;
		while(saque<=60){
			fazRetirada(saque);
			System.out.println(saque+"\t\t"+n50+"\t\t"+n10+"\t\t"+n5+"\t\t"+n1);
			saque = saque + 1;
		}

	}
}