#include <iostream>
#include <cmath>

#include "integracao.hpp"

double func(double _x) {
	return cos(_x) - _x;
}

int main() {
	std::cout << "Integral pelo metodo do trapezio: " << trapezio(func, {0, 10}, 100) << std::endl;
	std::cout << "Integral pela regra de um terco de simpson: " << terco_simpson(func, {0, 10}, 100) << std::endl;
	
	return 0;
}
