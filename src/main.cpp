#include <iostream>
#include <cmath>

#include "mathio.hpp"

int main() {
	std::cout << "f(x) = ";
	auto f = ler_funcao({"x"});
	std::cout << "g(x) = ";
	auto g = ler_funcao({"x"});
	
	if(f != nullptr) {
		gerar_grafico("C:\\dados\\func.dat", f, {-1, 1}, 1E-2);
	
	}
	
	if(g != nullptr) {
		gerar_grafico("C:\\dados\\gunc.dat", g, {-1, 1}, 1E-2);
		
	}
	
	std::cout << "Graficos gerados\n";
	
	return 0;
}
