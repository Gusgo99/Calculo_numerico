#include <iostream>
#include <cmath>
#include <vector>
#include <functional>

#include "EDO.hpp"

std::function<double(double)> euler_EDO(std::function<double(double, double)> f, intervalo_t _I, double _a, double _passo) {
	std::vector<double> _solucao = {_a};
	
	if(f == nullptr) return nullptr;
	
	for(auto i = (_I.first + _passo); i <= _I.second; i += _passo) {
		_solucao.push_back(f(i, _solucao.back()) * _passo + _solucao.back());
		
	}
	
	return [=](double _x) -> double {
		if((_x < _I.first) || (_x > _I.second)) {
#warning TODO: Implementar classe para exception
			throw -1;
			
		}
		_x -= _I.first;
		_x /= _passo;
		return _solucao[int(_x + 0.5)];};
}
