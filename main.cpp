#include <iostream>
#include <cmath>

#include "SEL.hpp"
#include "zeros.hpp"

SEL sel = {{1, 2, 3, 14}, {5, 7, 11, 52}, {13, 17, 23, 116}};

int main() {
	auto solucoes = gauss_sel(sel);
	
	printf("Solucoes:\n");
	for(auto i = 0; i != solucoes.size(); i++) {
		printf("x%i = %lf\n", i, solucoes[i]);
		
	}
	
	return 0;
}
