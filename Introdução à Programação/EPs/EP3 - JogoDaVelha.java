/**   Terceiro Exercício-Programa                                   **/
/**   01/06/2020                                                    **/
/*********************************************************************/

/*
	Jogo da Velha - programa para verificar o status de um jogo.
	
	Lista de Status calculado:
	0 - Jogo não iniciado: o tabuleiro está 'vazio', isto é sem peças X e O;
    1 - Jogo encerrado1: o primeiro jogador (que usa as peças X) é o ganhador;
    2 - Jogo encerrado2: o segundo jogador (que usa as peças O) é o ganhador;
    3 - Jogo encerrado3: empate - todas as casas do tabuleiro estão preenchidas com X e O, mas nenhum dos jogadores ganhou;
    4 - Jogo já iniciado e em andamento: nenhuma das alternativas anteriores.	
*/

public class JogoDaVelha {
	static final char pecaX = 'X';
	static final char pecaY = 'O';
	static final char espacoVazio = ' ';

	/*
		Método auxiliar, desenvolvido a fim de identificar o ganhador da partida de Jogo da Velha, caso
		houver - o que corresponde aos status 1 e 2.
		
		Entrada:
			Arranjo representando o tabuleiro;
			A peça a ser analisada (X ou Y);
			Número que será atribuído de acordo com o status testado.
			
		Saída:
			Número inteiro contendo o status da partida, de acordo com o parâmetro passado.
			Caso não haja um ganhador, ou seja, o status não for nem 1 nem 2, o método retornará -1.
	*/
	static int Ganhador (char [][] arranjo, char peca, int numero) {
		int statusLocal = -1;
		for (int i = 0; i<arranjo.length; i++) {
			for (int j = 0; j<arranjo[0].length; j++) {
				// Vencedor pelo preenchimento de uma linha completa.
        		if (arranjo[0][j]==peca && arranjo[1][j]==peca && arranjo[2][j]==peca) statusLocal = numero;
				// Vencedor pelo preenchimento de uma coluna completa.
				if (arranjo[i][0]==peca && arranjo[i][1]==peca && arranjo[i][2]==peca) statusLocal = numero;
				// Vencedor pelo preenchimento de uma das diagonais - principal ou secundária.
        		if (arranjo[0][2]==peca && arranjo[1][1]==peca && arranjo[2][0]==peca) statusLocal = numero;
				if (arranjo[0][0]==peca && arranjo[1][1]==peca && arranjo[2][2]==peca) statusLocal = numero;
			}
		}
	
		return (statusLocal);
	}

	/*
		Método auxiliar, desenvolvido a fim de identificar se um tabuleiro de jogo encontra-se vazio, ou
		seja, preenchido apenas com espaços em branco.
		
		Entrada:
			Arranjo representando o tabuleiro;
			A peça a ser analisada (espacoVazio);
			
		Saída:
			Variável vazio, do tipo boolean. Conterá o valor lógico true - caso o tabuleiro esteja vazio -,
			e false, caso não esteja.
	*/
	static boolean Vazio (char [][] arranjo, char espacoVazio) {
		boolean vazio = true;
		for (int i = 0; i<arranjo.length; i++) {
			for (int j = 0; j<arranjo.length; j++) {
				if (arranjo[i][j] != espacoVazio) vazio = false;
			}
		}
		return (vazio);
	}

	/*
		Método auxiliar, desenvolvido a fim de identificar se um tabuleiro de jogo encontra-se incompleto, ou
		seja, não preenchido por completo - ainda existem espaços em branco.
		
		Entrada:
			Arranjo representando o tabuleiro;
			A peça a ser analisada (espacoVazio);
			
		Saída:
			Variável incompleto, do tipo boolean. Conterá o valor lógico true - caso o tabuleiro não esteja 
			preenchido inteiramente - e false, caso esteja.
	*/
	static boolean NaoPreenchido (char [][] arranjo, char espacoVazio) {
		boolean incompleto = false;
		for (int i = 0; i<arranjo.length; i++) {
			for (int j = 0; j<arranjo.length; j++) {
				if (arranjo[i][j] == espacoVazio) incompleto = true;
			}
		}
		return (incompleto);
	}

	/*
		Determina o status de uma partida de Jogo da Velha
		
		Entrada:
			tabuleiro - matriz 3x3 de caracteres representando uma partida valida de Jogo da Velha
			
		Saída:
			um inteiro contendo o status da partida (valores válidos de zero a quatro)
	*/
	static int verificaStatus(char[][] tabuleiro) {
		// Criação e inicialização da variável status com o valor padrão -1.
		int status = -1;

		/*
			Caso a variável boolean vazio possua o valor lógico true, status receberá 0, indicando que
			todas as posições da matriz estão preenchidas com espaços vazios.
		*/
		if (Vazio(tabuleiro,espacoVazio)==true) status = 0;

		/* 
			Chamada do método Ganhador () com a matriz tabuleiro e pecaX, dado que o jogador com as peças
			X começa a partida antes do jogador O. Caso o jogador X satisfaça uma das condições para a 
			vitória, status receberá 1. Caso contrário, terá recebido o valor padrão -1.
		*/
        if (status==-1) status = Ganhador (tabuleiro, pecaX, 1);

		/*
			Caso a variável status contenha o valor padrão -1, o método Ganhador () é chamado novamente, 
			desta vez com a pecaY. Apenas se o jogador com as peças X não houver ganhado, e se o jogador
			com as peças O houver satisfeito uma das condições para a vitória, status receberá 2.
		*/
		if (status==-1) status = Ganhador (tabuleiro, pecaY, 2);

		/*
			Caso a matriz não esteja incompleta - ou seja, esteja preenchida por inteiro -, e
			status não for igual a 1 nem a 2, status receberá 3. Isso indica que o jogo foi finalizado,
			com o tabuleiro completo, mas sem um ganhador.
		*/
		if (status!=1 && status!=2 && NaoPreenchido(tabuleiro,espacoVazio)==false) status = 3;

		/*
			Caso a matriz não esteja vazia, e sim incompleta - ou seja, existem espaços vazios, mas eles
			não correspondem à matriz inteira -, e status não for igual a 1 nem a 2, indicando que não há
			um ganhador, status receberá 4. Isso representará que o jogo ainda não foi finalizado: existem
			espaços vazios, e não se tem um vencedor.
		*/
		if (status!=1 && status!=2 && NaoPreenchido(tabuleiro,espacoVazio)==true && Vazio(tabuleiro,espacoVazio)==false) status = 4;
		
		// O método retorna a variável status.
		return status;
	}
	
	/*
		Apenas para seus testes. 
	*/
	public static void main(String[] args) {
	// escreva seu código (para testes) aqui

	char[][] tab0 = {{' ',' ',' '},{' ',' ',' '},{' ',' ',' '}};
    char[][] tab1 = {{'X','X','X'},{'O','O',' '},{' ',' ',' '}};
    char[][] tab2 = {{'O','X','X'},{'X','O','O'},{' ',' ','O'}};
    char[][] tab3 = {{'O','X','X'},{'X','O','O'},{'O','X','X'}};
    char[][] tab4 = {{' ',' ',' '},{'X','O','X'},{' ',' ',' '}};

    System.out.println("Status calculado: " + verificaStatus(tab0));
    System.out.println("Status esperado para o tabuleiro0: 0\n");

    System.out.println("Status calculado: " + verificaStatus(tab1));
    System.out.println("Status esperado para o tabuleiro1: 1\n");

    System.out.println("Status calculado: " + verificaStatus(tab2));
    System.out.println("Status esperado para o tabuleiro2: 2\n");
    
    System.out.println("Status calculado: " + verificaStatus(tab3));
    System.out.println("Status esperado para o tabuleiro1: 3\n");
    
    System.out.println("Status calculado: " + verificaStatus(tab4));
    System.out.println("Status esperado para o tabuleiro4: 4\n");
	
	}

}