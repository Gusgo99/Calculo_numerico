#include <iostream>
#include <string>
#include <list>

#include "mathio.hpp"


int main() {
	std::list<std::pair<double, double>> _dados;
	
	auto f = ler_funcao({"x"});
	
	gerar_grafico("dados.dat", f, {0, 50}, 0.1);
	
	printf("Graficos gerados.");
	
	return 0;
}
