//package trabalho2;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.Scanner;

public class Leitura {
	
	public static void lerArquivo(Ordenacao o, String nElem, int n, int opcao){
		BufferedReader bR = null;
		String[] vetor = null; // Vetor de dados para 1 fila do arquivo
		float[] vetorInt = new float[n]; // Vetor para armazenar os dados como float
		
		try{
			// Leitura do arquivo escolhido usando uma String com o número de elementos.
			bR = new BufferedReader(new FileReader("vetor"+nElem+".txt"));
			String row = "";
			while((row = bR.readLine()) != null){
				vetor = row.split(" ");

				// Passagem de cada elemento de String para float e inserção no vetor.
				for (int i = 0; i < n; i++) {
					vetorInt[i] = Float.parseFloat(vetor[i]); 
				}

				/* 
				De acordo com a opção desejada, o método de ordenação é executado 
				com o auxílio de um objeto da classe Ordenacao.
				*/
				switch(opcao) {
					case 1: 
						o.BinaryInsertionSort(vetorInt,n);
						break;
					case 2:
						o.BinaryInsertionSortR(vetorInt,n);
						break;
					case 3:
						o.InsertionSort(vetorInt,n);
						break;
					case 4: 
						o.InsertionSortR(vetorInt,n);
						break;
					case 5:
						break;
					default:
						break;
				}
				
				/*
				Impressão dos elementos na tela após a ordenação. Há a impressão
				de uma linha em branco para separar os vetores.
				*/
				for (int i = 0; i < n; i++) {
					System.out.print(vetorInt[i] + " ");
				}
				System.out.println("\n");
			}
			
		} catch (FileNotFoundException e){
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
		
	}
	
	static int exibeOpcoes() {
        Scanner input = new Scanner(System.in);

    	System.out.println("========================================================");
    	System.out.println("|                  OPCOES DE ORDENACAO                  |");
    	System.out.println("========================================================");
    	System.out.println("|      1. Binary Insertion Sort versão iterativa;      |");
    	System.out.println("|      2. Binary Insertion Sort versão recursiva;      |");
    	System.out.println("|      3. Insertion Sort versão iterativa;             |");
		System.out.println("|      4. Insertion Sort versão recursiva;             |");
    	System.out.println("|      5. Sair;                                         |");
    	System.out.println("========================================================");
        System.out.println("Digite a opção a ser executada: ");
		
        int opcao = input.nextInt();
        return opcao;    
    }
		
	public static void main(String[] args) {
		Scanner input = new Scanner(System.in);
		Ordenacao ordena = new Ordenacao();
		int opcaoEscolhida;

		// O programa principal se repete até que o usuário escolha a opção 5 (Sair).
		do {
			opcaoEscolhida = exibeOpcoes();
			if (opcaoEscolhida == 5) {
				System.out.println("Saindo...");
				break;
			}

			System.out.println("Digite o número de elementos a serem ordenados (5,10,50,100,500,1000,5000,10000): ");
			String nElem = input.nextLine();
			int n = Integer.parseInt(nElem); 
			lerArquivo(ordena,nElem,n,opcaoEscolhida);

		} while(opcaoEscolhida != 5);
		 

	}

}
