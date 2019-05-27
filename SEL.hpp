#ifndef SEL_HPP
#define SEL_HPP

#include <array>
#include <stack>
#include <vector>

const uint32_t LIMIT_SEL = 1000;

class SEL {
	public:
		// Construtor da classe, define quantas variaveis o sistema tera.
		SEL(const size_t _vars);
		// Mostra o SEL na stdout
		void mostrar_SEL();
		// Recebe o SEL pela stdin
		void receber_SEL();
		// Recebe um vetor de equacoes, sendo o membro first um vetor com os coeficientes e o second os termos independentes
		void set_equacoes(const std::vector<std::pair<std::vector<double>, double>> &_equacoes);
		// Retorna o sistema de equacoes no mesmo formato que o set_equacoes
		std::vector<std::pair<std::vector<double>, double>> get_equacoes();
		// Recebe uma solucao estimada e retorna o residuo baseado no sistema recebido pela classe
		std::vector<double> calcular_residuo(const std::vector<double> &_estimativa);
		// Retorna solucao do sistema pelo metodo direto de Gauss
		std::vector<double> gauss_direto();
		// Retorna solucao do sistema pelo metodo do pivoteamento completo
		std::vector<double> pivoteamento_completo();
#warning TODO: Implementar metodo da fatoracao LU
		std::vector<double> fatoracao_LU();
		// Tenta tornar a matriz do sistema uma matriz com diagonal dominante
		void tornar_principal_dominante();
		// Resolve o sistema pelo metodo de Gauss Jacobi
		std::vector<double> gauss_jacobi(const double _erro);
		std::vector<double> gauss_jacobi(const std::vector<double> &_inicial, const double _erro);
		// Resolve o sistema pelo metodo de Gauss Seidel
		std::vector<double> gauss_seidel(double _erro);
		std::vector<double> gauss_seidel(std::vector<double> _inicial, const double _erro);
	
	private:
		// Numero de variaveis do sistema
		size_t vars;
		// Equacoes do sistema
		std::vector<std::pair<std::vector<double>, double>> equacoes;
		// Aproxima a matriz do sistema de uma matriz triangular
		void abaixar_zeros(const size_t _inicio);
		// Faz com que equacoes que possuam coeficientes maiores aparecam primeiro
		void dominantes(const size_t _inicio);
		// Soma a linha1 com um multiplo da linha2
		// _linha1 += _m * _linha2
		void soma_linhas(const size_t _linha1, const size_t _linha2, const double _m);
		// Recebe as equacoes do sistema e resolve. _var indica qual variavel deve ser encontrada com cada equacao.
		std::vector<double> resolve_escalonado(std::stack<std::pair<std::vector<double>, double>> &_sistema, std::stack<size_t> &_var);
	
};

#endif