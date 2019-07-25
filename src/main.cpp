#include <iostream>
#include <cmath>

#include "interpolacao.hpp"

int main() {
	std::vector<std::pair<double, double>> pontos = {{-1, 2}, {0, 3}, {1, 13}, {2, 13}, {3, 14}, {4, 14}, {5, 14}, {6, 15}, {7, 20}, {8, 22}};
	
	interpol_poli pol;
	
	pol.metodo_newton(pontos);
	
	pol.print_coefs();
	
	for(auto i: pontos) {
		std::cout << "f(" << i.first << ") = " << pol(i.first) << std::endl;
		
	}
	
	return 0;
}
