/**                   Segundo Exercício-Programa                    **/
/**   06/05/2020                                                    **/
/*********************************************************************/

/*
	Cálculo para raiz quadrada
*/
public class Raiz {
	
	/* 
		Método auxiliar, criado a fim de calcular o módulo de
		um número. Caso este seja maior ou igual a zero, o método
		retornará o próprio número. Caso contrário, retornará o
		oposto do número. 
	*/
	static double Modulo (double numero) {
		if (numero >= 0) return (numero);
		else return (-1*numero);
	}

	/*
		Calcula a raiz quadrada de um valor, com uma determinada
		precisão. Retorna esse valor, ou -1 quando:
		* a < 0
		* epsilon <= 0
		* epsilon >= 1
		
		Ou 0 (zero) quando a = 0
		
		Parâmetro:
			a - valor cuja raiz quadrada será calculada
			epsilon - precisão do cálculo
	*/

	static double raizQuadrada(double a, double epsilon) {
        // O método retorna -1 caso a<0, epsilon<=0 ou epsilon>=1.
		if (a < 0 || epsilon <= 0 || epsilon >= 1) return (-1);
		/* 
			Como o método de Newton não aceita o valor a = 0, 
			o método raizQuadrada() retornará 0 previamente nesse caso.
		*/
		if (a==0) return (0);
			// Declaração e atribuição de "true" à variável boolean continuar.
			boolean continuar = true;
			/*
				Declaração e atribuição de valor às variáveis x0 e x1, de
				tipo double - a fim de permitir divisões com resto -, 
				seguindo o método de Newton para cálculo da raiz quadrada.
			 */
            double x0 = a/2.0;
            double x1 = (1.0/2.0) * (x0 + (a/x0));
			/*
				Declaração e atribuição de valor às variáveis xAnterior e 
				xNovo, que inicialmente recebem, respectivamente, o valor
				de x0 e x1.
			*/
			double xAnterior = x0;
			double xNovo = x1;

			/*
				xNovo receberá um novo valor, a partir do cálculo de Newton, 
				a cada vez que o módulo de (xNovo - xAnterior) for maior ou
				igual a zero. Posteriormente, a variável xAnterior é atualizada,
				recebendo o valor de xNovo. Caso a operação resulte em um 
				valor menor que 0, a variável continuar, do tipo boolean, 
				receberá false, interrompendo o laço.
			*/
			while (continuar == true) {
				xNovo = (1.0/2.0) * (xAnterior + (a/xAnterior));
				if (Modulo(xNovo-xAnterior) < epsilon) continuar = false;
				xAnterior = xNovo;
			}
			/* 
				Por fim, o método retorna o valor de xNovo, correspondendo à
				raiz quadrada do número a.
			*/
			return (xNovo);
	}

	/*
		Apenas para seus testes. ISSO SERA IGNORADO NA CORREÇÃO
	*/
	public static void main(String[] args) {
		// Exemplo de teste:
		for (int i = 0; i<=100; i++) {
			double padrao = Math.sqrt(i);
			double metodo = raizQuadrada(i,0.0001);
			double erro = Modulo(padrao-metodo);
			System.out.println(i+"  " + padrao + "  " + metodo + "  " + erro);
		}
	}
}