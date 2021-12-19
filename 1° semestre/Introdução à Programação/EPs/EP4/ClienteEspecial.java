
public class ClienteEspecial extends Cliente{
	static final int dividaMaxima = 50000;
	static final String tipo = "CE";
	
	/* Construtor da Classe ClienteEspecial
	 * Este construtor invoca o construtor da classe Cliente.
	 */
	ClienteEspecial(String nome, int cpf, int valor){
		super(nome, cpf, valor);
	}
	
	/* Metodo que retorna o valor do atributo tipo do objeto atual */
	String retornaTipo() {
		return tipo;
	}
	
	/* Metodo para o cliente atual obter um emprestimo de acordo com o valor passado por parametro.
	 *   O método da classe Cliente foi sobrescrito, dado que o valor da constante dividaMaxima é 
	 *   diferente para clientes especiais. Para acessar os métodos da superclasse, utilizou-se
	 *   "super".
	 *   Caso o valor do parametro seja menor ou igual a zero, o metodo deve retornar false
	 *   Caso contrario ha duas situacoes:
	 *     1a) se o valor do parametro mais o valor do atributo valorDaDivida for maior do
	 *         que o valor da constante dividaMaxima, o metodo deve retornar false 
	 *     2a) caso contrario, o atributo valorDaDivida deve ser incrementado em valor, o atributo
	 *         valorContaCorrente deve ser incrementado em valor e o metodo deve retornar true
	 */
	public boolean obterEmprestimo(int valor) {
		if (valor <= 0) return (false);
		if ((valor + super.getValorDaDivida()) > dividaMaxima) return (false);
		else {
			super.setValorDaDivida(super.getValorDaDivida() + valor);
			super.setValorContaCorrente(super.getValorContaCorrente() + valor);
			return (true);
		}
	}
	
}
