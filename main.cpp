#include <iostream>
#include <string>
#include <list>

#include "mathio.hpp"


int main() {
	std::list<std::pair<double, double>> _dados;
	
	auto f = ler_funcao({"x"});
	
	for(auto i = 0.00; i < 50; i += 0.1) {
		_dados.push_back(std::pair(i, f({i})));
		
	}
	
	gerar_grafico("dados.dat", _dados.begin(), _dados.end());
	
	printf("Graficos gerados.");
	
	return 0;
}
