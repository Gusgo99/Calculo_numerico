#include <iostream>
#include <string>
#include <list>

#include "EDO.hpp"
#include "mathio.hpp"

int main() {
	auto a = 0.00;
	auto b = 0.00;
	auto y0 = 0.00;
	
	printf("Digite a EDO: ");
	auto EDO = ler_funcao({"x", "y"});
	printf("Digite o intervalo([a, b]): ");
	scanf(" [%lf, %lf]", &a, &b);
	printf("Digite o valor inicial(y0): ");
	scanf(" %lf", &y0);
	printf("Digite a solucao: ");
	auto solAna = ler_funcao({"x"});
	
	auto solNum = euler_EDO([EDO](double _x, double _y) {return EDO({_x, _y});}, {a, b}, y0, 0.001);
	
	printf("Gerando graficos.\n");
	
	gerar_grafico("C:\\dados\\solNum.dat", [solNum](std::vector<double> _arg) {return solNum(_arg.front());}, std::pair(a, b), 0.001);
	gerar_grafico("C:\\dados\\solAna.dat", solAna, std::pair(a, b), 0.001);
	gerar_grafico("C:\\dados\\erro.dat", [solNum, solAna] (std::vector<double> _arg) {return solNum(_arg.front()) - solAna(_arg);}, std::pair(a, b), 0.001);
	
	printf("Graficos gerados.\n");
	
	return 0;
}
