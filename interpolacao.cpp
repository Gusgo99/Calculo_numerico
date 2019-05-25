#include <algorithm>
#include <iostream>

#include "interpolacao.hpp"

void interpol_poli::ordenar_pontos(std::vector<std::pair<double, double>> &_pontos) {
	std::sort(_pontos.begin(), _pontos.end(), [](std::pair<double, double> _a, std::pair<double, double> _b) {return _a.first < _b.first;});
	
	return;
}

void interpol_poli::verifica_repeticao(std::vector<std::pair<double, double>> &_pontos) {
	if(std::adjacent_find(_pontos.begin(), _pontos.end(), [](std::pair<double, double> _a, std::pair<double, double> _b) {return _a.first == _b.first;}) != _pontos.end()) {
#warning TODO: Criar classe para exception
		throw -1;
		
	}
	
	return;
}

void interpol_poli::print_coefs() {
	for(auto i: coefs) {
		std::cout << i << " ";
		
	}
	std::cout << "\n";
	
	return;
}

void interpol_poli::forma_lagrange(std::vector<std::pair<double, double>> _pontos) {
	ordenar_pontos(_pontos);
	std::vector<std::vector<double>> _coefsLagrange(_pontos.size());
	
	coefs.clear();
	
	// Calcula cada polinomio de Lagrange
	for(auto i = 0; i != _pontos.size(); i++) {
		double _div = 1;
		_coefsLagrange[i].push_back(1);
		// Realiza o produtorio do polinomio
		for(auto j = 0; j != _pontos.size(); j++) {
			if(i != j) {
				// Realiza produto de polinomio (x - xi) * (ax^n + bx^(n - 1) + ...) = ax^(n + 1) + bx^n + c x^(n - 1) ... - xi*(ax^n + bx^(n - 1) + ...)
				_coefsLagrange[i].insert(_coefsLagrange[i].begin(), 0);
				for(auto k = 0; k != _coefsLagrange[i].size() - 1; k++) {
					_coefsLagrange[i][k] -= _pontos[j].first * _coefsLagrange[i][k + 1];
					_coefsLagrange[i][k] /= _pontos[i].first - _pontos[j].first;
					
				}
				_coefsLagrange[i][_coefsLagrange[i].size() - 1] /= _pontos[i].first - _pontos[j].first;
				
			}
		}
	}
	
	coefs = _coefsLagrange[0];
	
	for(auto i = 0; i != coefs.size(); i++) {
		coefs[i] *= _pontos[0].second;
		
	}
	
	for(auto i = 1; i != _coefsLagrange.size(); i++) {
		for(auto j = 0; j != _coefsLagrange[i].size(); j++) {
			coefs[j] += _pontos[i].second * _coefsLagrange[i][j];
			
		}
	}
	
	intervalo.first = _pontos.front().first;
	intervalo.second = _pontos.back().first;
	
	return;
}

double interpol_poli::operator()(double _x) {
	double _y = 0;
	double _pot = 1;
	
	if((_x < intervalo.first) || (_x > intervalo.second)) {
#warning TODO: Implementar classe para exception
		throw -1;
		
	}
	
	for(auto i = 0; i != coefs.size(); i++) {
		_y += coefs[i] * _pot;
		_pot *= _x;
		
	}
	
	return _y;
}
