#include <iostream>
#include <utility>
#include <list>
#include <cmath>

typedef std::pair<double, double> intervalo_t;

std::list<intervalo_t> find_interval(double (*f)(double), intervalo_t _I, double _step);
double bisseccao(double (*f)(double), intervalo_t _I, double _erro);
double ponto_fixo(double (*f)(double), double (*fi)(double), intervalo_t _I, double _erro);

double f(double _x) {
	return exp(_x) - (_x * _x) + 4;
	//return (_x * _x) - (3 * _x) + 2;
	//return (_x * _x) - 5;
	//return (_x * _x) - 2;
	//return (_x * _x) + _x - 6;
	//return (_x * _x * _x) - (6 * _x * _x) + (11 * _x) - 6;
	//return log(_x) * log(_x) - 15 * _x;
}

double fi(double _x) {
	return sqrt(exp(_x) + 4);
	//return -sqrt(6 - _x);
}

int main() {
	std::list<intervalo_t> intervalos = find_interval(f, {-1E5, 1E5}, 1);
	std::list<double> zeros;
	
	for(auto i: intervalos) {
		printf("Intervalo com zero: [%.2lf, %.2lf]\n", i.first, i.second);
		//zeros.push_back(bisseccao(f, i, 1E-15));
		zeros.push_back(ponto_fixo(f, fi, i, 1E-15));
		
	}
	
	for(auto i: zeros) {
		printf("Zeros encontrados: %.15lf\n", i);
		
	}
	
	return 0;
}

std::list<intervalo_t> find_interval(double (*f)(double), intervalo_t _I, double _step) {
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