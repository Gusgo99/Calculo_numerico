#include <iostream>
#include <string>

#include "mathio.hpp"

int main() {
	printf("f(x, y) = ");
	
	auto f = ler_funcao({"x", "y"});
	
	// Verifica se 
	if(f != nullptr)
		printf("f(1, 2) = %lf\n", f({1, 2}));
	else
		printf("You're dereferencing a null pointer. Open your eyes!\n");
	
	return 0;
}
