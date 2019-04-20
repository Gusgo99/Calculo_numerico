#include <array>
#include <cmath>
#include <iostream>

#include "zeros.hpp"

std::list<intervalo_t> encontra_intervalos(std::function<double(double)> f, intervalo_t _I, double _step) {
	std::list<intervalo_t> intZeros;
	
	for(auto i = _I.first; i < _I.second; i += _step) {
		// Verifica se a funcao troca de sinal no interior do intervalo [i, i + _step]
		if((f(i) * f(i + _step)) < 0) {
			// Se ocorre troca de sinal, considera que o intervalo possui zero
			intZeros.push_back({i, i + _step});
			
		}
		else if(f(i) == 0) {
			// Se a função for igual a zero no ponto i, adiciona um invervalo contendo somente o ponto do zero
			intZeros.push_back({i, i});
			
		}
	}
	
	return intZeros;
}

double bisseccao(std::function<double(double)> f, intervalo_t _I, double _erro) {
	double _med = (_I.first + _I.second) / 2;
	_erro = fabs(_erro);
	uint32_t count = 0;
	
	if(f == nullptr) return nan("");
	
	while(fabs(_I.first - _I.second) > _erro) {
		// Verifica de qual lado do intervalo o zero esta e corta o intervalo no meio
		if((f(_I.first) * f(_med)) < 0) {
			_I.second = _med;
			
		}
		else {
			_I.first = _med;
			
		}
		
		_med = (_I.second + _I.first) / 2;
		
		// Termina procura se o programa passar do limite de iteracoes
		if(++count > LIMIT) break;
		
	}
	
#ifdef COMPARAR
	printf("%i iteracoes pelo metodo da bisseccao\n", count);
#endif
	
	return _med;
}

double ponto_fixo(std::function<double(double)> f, std::function<double(double)> fi, intervalo_t _I, double _erro) {
	double _xn = 0.00, _xn1 = 0.00;
	uint32_t count = 0;
	
	if(f == nullptr) return nan("");
	if(f == nullptr) return nan("");
	
	double _med = (_I.first + _I.second) / 2;
	// Utiliza media dos valores para encontrar a extremidade do intervalo mais proximo do zero
	if(fi(_med) > _med) {
		_xn1 = _I.second;
		
	}
	else {
		_xn1 = _I.first;
		
	}
	
	do {
		_xn = _xn1;
		_xn1 = fi(_xn);
		
		if(++count > LIMIT) break;
		
	} while(fabs(_xn1 - _xn) > _erro);
	
#ifdef COMPARAR
	printf("%i iteracoes pelo metodo do ponto fixo\n", count);
#endif
	
	return _xn1;
}

double tangente(std::function<double(double)> f, std::function<double(double)> dfdx, intervalo_t _I, double _erro) {
	double _xn, _xn1;
	uint32_t count = 0;
	
	// Funcao iterativa:
	auto fit = [&](double _x) {return _x - (f(_x) / dfdx(_x));};
	
	if(f == nullptr) return nan("");
	if(dfdx == nullptr) return nan("");
	
	double _med = (_I.first + _I.second) / 2;
	// Utiliza media dos valores para encontrar a extremidade do intervalo mais proximo do zero
	if(f(fit(_med)) > _med) {
		_xn1 = _I.second;
		
	}
	else {
		_xn1 = _I.first;
		
	}
	
	do {
		// Executa a funcao iterativa ate que o erro esteja de acordo com o desejado
		_xn = _xn1;
		_xn1 = fit(_xn);
		
		if(++count > LIMIT) break;
		
	} while(fabs(_xn1 - _xn) > _erro);
	
#ifdef COMPARAR
	printf("%i iteracoes pelo metodo da tangente\n", count);
#endif
	
	return _xn1;
}

double secante(std::function<double(double)> f, intervalo_t _I, double _erro) {
	std::array<double, 3> _xn = {_I.first, _I.second, 0};
	uint32_t count = 0;
	auto pos = 2;
	
	// Funcao ITerativa:
	auto fit = [&](double _x1, double _x2) {return ((_x1 * f(_x2)) - (_x2 * f(_x1))) / (f(_x2) - f(_x1));};
	
	if(f == nullptr) return nan("");
	
	// Executa a funcao iterativa ate que o erro esteja de acordo com o desejado
	for(pos = 2; fabs(_xn[(pos + 1) % 3] - _xn[(pos + 2) % 3]) > _erro; pos++) {
		_xn[pos % 3] = fit(_xn[(pos + 1) % 3], _xn[(pos + 2) % 3]);
		
		if(++count > LIMIT) break;
		
	}
	
#ifdef COMPARAR
	printf("%i iteracoes pelo metodo da secante\n", count);
#endif
	
	return _xn[(pos + 2) % 3];
}