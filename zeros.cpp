#include <cmath>
#include <iostream>

#include "zeros.hpp"

std::list<intervalo_t> encontra_intervalos(double (*f)(double), intervalo_t _I, double _step) {
	std::list<intervalo_t> intZeros;
	
	for(auto i = _I.first; i < _I.second; i += _step) {
		if((f(i) * f(i + _step)) < 0) {
			intZeros.push_back({i, i + _step});
			
		}
		else if(f(i) == 0) {
			intZeros.push_back({i, i});
			
		}
	}
	
	return intZeros;
}

double bisseccao(double (*f)(double), intervalo_t _I, double _erro) {
	double _med = (_I.first + _I.second) / 2;
	_erro = fabs(_erro);
	
	if(f == nullptr) return 0.00;
	
	while(fabs(_I.first - _I.second) > _erro) {
		if((f(_I.first) * f(_med)) < 0) {
			_I.second = _med;
			
		}
		else {
			_I.first = _med;
			
		}
		
		_med = (_I.second + _I.first) / 2;
	}
	
	return _med;
}

double ponto_fixo(double (*f)(double), double (*fi)(double), intervalo_t _I, double _erro) {
	double _xn = 0.00, _xn1 = 0.00;
	
	if(f == nullptr) return 0.00;
	if(f == nullptr) return 0.00;
	
	double _med = (_I.first + _I.second) / 2;
	if(fi(_med) > _med) {
		_xn1 = _I.second;
		
	}
	else {
		_xn1 = _I.first;
		
	}
	
	do {
		_xn = _xn1;
		_xn1 = fi(_xn);
		printf("_xn = %lf | _xn1 = %lf\n", _xn, _xn1);
		
	} while(fabs(_xn1 - _xn) > _erro);
	
	return _xn1;
}

double tangente(double (*f)(double), double (*dfdx)(double), intervalo_t _I, double _erro) {
	
	return 0.0;
}

double secante(double (*f)(double), intervalo_t _I, double _erro) {
	
	return 0.0;
}