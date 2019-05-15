#include <iostream>
#include <cmath>

#include "SEL.hpp"
#include "zeros.hpp"

int main() {
	SEL teste(3);
	
	teste.set_equacoes({{{1, 5, 1}, 14}, {{3, 1, 1}, 8}, {{1, 1, 2}, 9}});
	
	teste.mostrar_SEL();
	
	teste.tornar_principal_dominante();
	
	//auto s = teste.gauss_direto();
	//auto s = teste.pivoteamento_completo();
	//auto s = teste.gauss_jacobi(1E-15);
	auto s = teste.gauss_seidel(1E-15);
	
	for(auto i: s) {
		std::cout << i << " ";
		
	}
	std::cout << "\n";
	
	return 0;
}
