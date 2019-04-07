#include <iostream>
#include <cmath>

#include "zeros.hpp"

// Funcao que se deseja encontrar o zero
double f(double _x);

int main() {
	std::list<intervalo_t> intervalos = encontra_intervalos(f, {-1E5, 1E5}, 1);
	std::list<double> zeros;
	
	for(auto i: intervalos) {
		printf("Intervalo com zero: [%.2lf, %.2lf]\n", i.first, i.second);
		zeros.push_back(bisseccao(f, i, 1E-15));
		
	}
	
	for(auto i: zeros) {
		printf("Zeros encontrados: %.15lf\n", i);
		
	}
	
	return 0;
}

double f(double _x) {
	return exp(_x) - (_x * _x) + 4;
	//return (_x * _x) - (3 * _x) + 2;
	//return (_x * _x) - 5;
	//return (_x * _x) - 2;
	//return (_x * _x) + _x - 6;
	//return (_x * _x * _x) - (6 * _x * _x) + (11 * _x) - 6;
	//return log(_x) * log(_x) - 15 * _x;
}

