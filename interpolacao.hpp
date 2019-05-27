#ifndef INTERPOLACAO_HPP
#define INTERPOLACAO_HPP

#include <vector>
#include <map>
#include <list>

// Classe para interpolacao polinomial
class interpol_poli {
	public:
		void forma_lagrange(std::vector<std::pair<double, double>> &_pontos);
		void metodo_newton(std::vector<std::pair<double, double>> &_pontos);
		double operator()(const double _x);
		void print_coefs();
	private:
		void ordenar_pontos(std::vector<std::pair<double, double>> &_pontos);
		void verifica_repeticao(const std::vector<std::pair<double, double>> &_pontos);
		std::map<std::list<size_t>, double> calcular_dif_div(const std::vector<std::pair<double, double>> &_pontos);
		// Multiplica um polinomio _a de grau n com um polinomio _b de grau 1
		void mult_pols(std::vector<double> &_a, const std::vector<double> &_b);
		void soma_pols(std::vector<double> &_a, const std::vector<double> &_b);
		std::vector<double> coefs;
		std::pair<double, double> intervalo;
		
};

#endif
