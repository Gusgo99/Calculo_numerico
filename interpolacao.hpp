#ifndef INTERPOLACAO_HPP
#define INTERPOLACAO_HPP

#include <vector>

// Classe para interpolacao polinomial
class interpol_poli {
	public:
		void forma_lagrange(std::vector<std::pair<double, double>> _pontos);
		void metodo_newton(std::vector<std::pair<double, double>> _pontos);
		double operator()(double _x);
		void print_coefs();
	private:
		void ordenar_pontos(std::vector<std::pair<double, double>> &_pontos);
		void verifica_repeticao(std::vector<std::pair<double, double>> &_pontos);
		std::vector<std::pair<double, double>> multiplica_polinomio(std::vector<std::pair<double, double>> _pol1, std::vector<std::pair<double, double>> _pol2);
		std::vector<double> coefs;
		std::pair<double, double> intervalo;
		
};

#endif
