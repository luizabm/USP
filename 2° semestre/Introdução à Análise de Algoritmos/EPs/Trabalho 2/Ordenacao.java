public class Ordenacao {

    /*
    FUNÇÃO BINARY INSERTION SORT VERSÃO ITERATIVA
    
    A função percorre todo o vetor e, a cada iteração,
    encontra o índice do arranjo em que o elemento deve
    ser inserido a fim de manter a ordenação dos elementos.
    Depois, realiza o deslocamento de dados necessário
    para a liberação de espaço e consequente inserção do 
    elemento.
    */
    static void BinaryInsertionSort(float [] A, int n) {
        for (int i = 1; i<n; i++) {
            int j = i-1;
            float aux = A[i];
            int indice = BinarySearch(A,aux,0,j);
            while (j >= indice) {
                A[j+1] = A[j];
                j--;
            }
            A[indice] = aux;
        }
    }

    /*
    FUNÇÃO AUXILIAR (BINARY SEARCH)

    Caso a condição para a busca seja válida (fim é
    maior ou igual a inicio), calcula-se o meio e
    altera-se as variáveis fim e inicio de acordo
    com a ordenação do vetor. Por fim, retorna-se
    inicio.
    */
    static int BinarySearch(float[] A, float chave, int inicio, int fim) {
        while (inicio <= fim) {
            int meio = (inicio+fim)/2;
            if(A[meio] > chave) fim = meio - 1;
            else inicio = meio + 1;
        }
        return inicio;
    }

    /*
    FUNÇÃO BINARY INSERTION SORT VERSÃO RECURSIVA

    A função é chamada recursivamente com o parâmetro
    n-1, restando ordenar o elemento do arranjo com
    índice n-1 (considerando o início em 0). Através
    da função auxiliar de busca binária recursiva, o
    índice do arranjo em que o elemento deve ser inserido
    a fim de manter a ordenação dos elementos é encontrado.
    Depois, ocorre o deslocamento de dados necessário
    para a liberação de espaço e consequente inserção do 
    elemento.
    */
    static void BinaryInsertionSortR(float [] A, int n) {
        if (n > 1) {
            BinaryInsertionSortR(A,n-1);
            float aux = A[n-1];
            int j = n-2;
            int indice = BinarySearchR(A,aux,0,j);
            while (j >= indice) {
                A[j+1] = A[j];
                j--;
            }
            A[indice] = aux;
        }
    }

    /*
    FUNÇÃO AUXILIAR (BINARY SEARCH RECURSIVA)

    Caso a condição para a busca seja válida (fim é
    maior ou igual a inicio), calcula-se o meio e
    altera-se as variáveis fim e inicio de acordo
    com a ordenação do vetor. Por fim, retorna-se
    inicio.
    */
    static int BinarySearchR (float [] A, float chave, int inicio, int fim) {
        if (fim >= inicio) {
            int meio = (inicio+fim)/2;
            if (A[meio] > chave) return BinarySearchR(A,chave,inicio,meio-1);
            else return BinarySearchR(A,chave,meio+1,fim);
        }
        return inicio;
    }

    /*
    FUNÇÃO INSERTION SORT VERSÃO ITERATIVA

    A função percorre todo o vetor e, a cada iteração,
    realiza comparações com os elementos à esquerda a fim
    de encontrar a posição onde o elemento deve ser inserido
    a fim de manter a ordenação. Assim, caso não esteja na
    posição correta, swaps são realizados a fim de liberar
    espaço para a inserção.
    */
    static void InsertionSort(float [] A, int n) {
        for (int i = 1; i < n; i++) {
            float aux = A[i];
            int j = i;
            while (j>0 && aux < A[j-1]) {
                A[j] = A[j-1];
                j--;
            }
            A[j] = aux;
        }
    }

    /*
    FUNÇÃO INSERTION SORT VERSÃO RECURSIVA

    A função é chamada recursivamente com o parâmetro
    n-1, restando ordenar o elemento do arranjo com
    índice n-1 (considerando o início em 0). São realizadas
    comparações com os elementos à esquerda a fim de encontrar
    a posição onde o elemento deve ser inserido. Caso não 
    esteja na posição correta, são realizados swaps a fim
    de liberar espaço para a inserção.
    */
    static void InsertionSortR (float [] A, int n) {
        if (n <= 1) return;
        InsertionSortR(A, n-1);
        float aux = A[n-1];
        int j = n-2;
        while (j >= 0 && A[j] > aux) {
            A[j+1] = A[j];
            j--;
        }
        A[j+1] = aux;
    }

    public static void main(String [] args) {
        
    }
}