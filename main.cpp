#include <iostream>
#include <cmath>
#include <fstream>

#define STEP 1E-3
#define Y0 0.0001
#define X0 1.00
#define X1 5.00

#include "EDO.hpp"

std::ofstream saida("data.dat");
std::ofstream adad("data2.dat");

int main() {
	auto x = euler_EDO([](double _x, double _y) {return (pow(_x, 2)* exp(_x) + _y) / _x;}, {X0, X1}, Y0, STEP);
	
	for(auto i = X0; i <= X1; i += STEP) {
		saida << i << " " << x(i) << std::endl;
		
	}
	
	for(auto i = X0; i <= X1; i += STEP) {
		adad << i << " " << (i * exp(i)) << std::endl;
		
	}
	printf("Programa finalizado.");
	
	return 0;
}
