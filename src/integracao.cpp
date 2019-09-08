#include <iostream>

#include "integracao.hpp"

double trapezio(std::function<double(double)> f, intervalo_t _I, unsigned _divisoes) {
	double _integral = 0.0;
	
	if(f != nullptr) {
		double _passo = (_I.second - _I.first) / _divisoes;
		auto _inicio = _I.first + _passo;
		auto _fim = _I.second - _passo;
		
		for(auto i = _inicio; i < _fim; i += _passo) {
			_integral += f(i);
			
		}
		_integral *= 2;
		_integral += f(_I.first);
		_integral += f(_I.second);
		_integral *= _passo / 2;
		
	}
	
	return _integral;
}

double terco_simpson(std::function<double(double)> f, intervalo_t _I, unsigned _divisoes) {
	double _integral = 0.0;
	double _mult = 4.0;
	
	if(f != nullptr) {
		_divisoes += (((_divisoes % 2) == 0) ? 0 : 1);
		double _passo = (_I.second - _I.first) / _divisoes;
		auto _inicio = _I.first + _passo;
		auto _fim = _I.second - _passo;
		
		for(auto i = _inicio; i < _fim; i += _passo) {
			_integral += _mult * f(i);
			_mult = (_mult == 2.0 ? 4.0 : 2.0);
			
		}
		_integral += f(_I.first);
		_integral += f(_I.second);
		_integral *= _passo / 3;
		
	}
	
	return _integral;
}
