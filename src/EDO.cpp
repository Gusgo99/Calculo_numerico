#include <vector>

class bad_dominio : public std::exception {
	const char* what() const noexcept {return "Tentativa de calcular o resultado da EDO em um ponto fora do intervalo calculado\n";};
	
};

#include "EDO.hpp"

std::function<double(double)> euler_EDO(std::function<double(double, double)> f, intervalo_t _I, double _a, double _passo) {
	std::vector<double> _solucao = {_a};
	
	if(f == nullptr) return nullptr;
	
	for(auto i = (_I.first + _passo); i <= _I.second; i += _passo) {
		_solucao.push_back(f(i, _solucao.back()) * _passo + _solucao.back());
		
	}
	
	return [=](double _x) -> double {
		if((_x < _I.first) || (_x > _I.second)) {
			throw bad_dominio();
			
		}
		_x -= _I.first;
		_x /= _passo;
		return _solucao[int(_x + 0.5)];};
}
