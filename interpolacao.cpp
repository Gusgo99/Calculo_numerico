#include <algorithm>
#include <iostream>
#include <utility>

#include "interpolacao.hpp"

void interpol_poli::ordenar_pontos(std::vector<std::pair<double, double>> &_pontos) {
	std::sort(_pontos.begin(), _pontos.end(), [](std::pair<double, double> _a, std::pair<double, double> _b) {return _a.first < _b.first;});
	
	return;
}

void interpol_poli::verifica_repeticao(const std::vector<std::pair<double, double>> &_pontos) {
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

void interpol_poli::mult_pols(std::vector<double> &_a, const std::vector<double> &_b) {
	_a.insert(_a.begin(), 0);
	for(size_t i = 0; i != _a.size() - 1; i++) {
		_a[i] += _b[0] * _a[i + 1];
		
	}
	
	return;
}

void interpol_poli::forma_lagrange(std::vector<std::pair<double, double>> &_pontos) {
	std::vector<std::vector<double>> _coefsLagrange(_pontos.size());
	
	ordenar_pontos(_pontos);
	verifica_repeticao(_pontos);
	
	intervalo.first = _pontos.front().first;
	intervalo.second = _pontos.back().first;
	
	coefs.clear();
	
	// Calcula cada polinomio de Lagrange
	for(size_t i = 0; i != _pontos.size(); i++) {
		_coefsLagrange[i].push_back(1);
		// Realiza o produtorio do polinomio
		for(size_t j = 0; j != _pontos.size(); j++) {
			if(i != j) {
				mult_pols(_coefsLagrange[i], {-_pontos[j].first, 1});
				for(size_t k = 0; k != _coefsLagrange[i].size() - 1; k++) {
					_coefsLagrange[i][k] /= _pontos[i].first - _pontos[j].first;
					
				}
				_coefsLagrange[i][_coefsLagrange[i].size() - 1] /= _pontos[i].first - _pontos[j].first;
				
			}
		}
	}
	
	coefs = _coefsLagrange[0];
	
	for(size_t i = 0; i != coefs.size(); i++) {
		coefs[i] *= _pontos[0].second;
		
	}
	
	for(size_t i = 1; i != _coefsLagrange.size(); i++) {
		for(size_t j = 0; j != _coefsLagrange[i].size(); j++) {
			coefs[j] += _pontos[i].second * _coefsLagrange[i][j];
			
		}
	}
	
	return;
}

void interpol_poli::metodo_newton(std::vector<std::pair<double, double>> &_pontos) {
	std::vector<std::vector<double>> _coefsLagrange(_pontos.size());
	
	// Garante que pontos sao diferentes e estao em ordem
	ordenar_pontos(_pontos);
	verifica_repeticao(_pontos);
	
	// Define intervalo em que a solucao e valida
	intervalo.first = _pontos.front().first;
	intervalo.second = _pontos.back().first;
	
	// Limpa coeficientes ja calculados
	coefs.clear();
	// Define numero de coeficientes
	coefs.resize(_pontos.size());
	
	// Calcula diferencas divididas
	auto _difDiv = calcular_dif_div(_pontos);
	
	std::pair<size_t, size_t> _pos = {0, 0};
	std::vector<double> _pol = {1};
	
	// Calcula combinacao linear dos polinomios
	for(size_t i = 0; i != _pontos.size(); i++) {
		for(size_t j = 0; j != _pol.size(); j++) {
			coefs[j] += _difDiv[_pos] * _pol[j];
			
		}
		mult_pols(_pol, {-_pontos[i].first, 1});
		_pos.second++;
	}
	
	return;
}

std::map<std::pair<size_t, size_t>, double> interpol_poli::calcular_dif_div(const std::vector<std::pair<double, double>> &_pontos) {
	std::map<std::pair<size_t, size_t>, double> _difDiv;
	
	// Calcula diferencas divididas:
	// Insere primeira coluna (Valores de y)
	for(size_t i = 0; i != _pontos.size(); i++) {
		_difDiv[{i, i}] = _pontos[i].second;
		
	}
	
	// Cada iteracao calcula uma coluna
	for(size_t i = 1; i != _pontos.size(); i++) {
		//_modelo.push_back(i);
		std::pair<size_t, size_t> _pos = {0, i};
		auto _acima = _pos;
		// Se a posicao for [x0, x1... xn], entao a posicao a esquerda acima sera [x0, x1... xn-1]
		_acima.second--;
		//_acima.pop_front();
		auto _abaixo = _pos;
		// Se a posicao for [x0, x1... xn], entao a posicao a esquerda abaixo sera [x1, x2... xn]
		_abaixo.first++;
		// Calcula cada diferenca dividida da coluna atual
		for(size_t j = i; j != _pontos.size(); j++) {
			// f[x0, x1..., xn] = (f[x1, x2... xn] - f[x0, x1... xn-1]) / (xn - x0)
			_difDiv[_pos] = (_difDiv[_abaixo] - _difDiv[_acima]) / (_pontos[_pos.second].first - _pontos[_pos.first].first);
			// Atualiza a posicao para a proxima linha (Se a linha atual e [x1, x2... xn] a proxima sera [x2, x3... xn+1]
			_pos.first++;
			_pos.second++;
			// Atualiza o valor superior e inferior, semelhante ao caso acima
			_acima.first++;
			_acima.second++;
			_abaixo.first++;
			_abaixo.second++;
			
		}
	}
	
	return std::move(_difDiv);
}

double interpol_poli::operator()(double _x) {
	double _y = 0;
	double _pot = 1;
	
	if((_x < intervalo.first) || (_x > intervalo.second)) {
#warning TODO: Implementar classe para exception
		throw -1;
		
	}
	
	for(size_t i = 0; i != coefs.size(); i++) {
		_y += coefs[i] * _pot;
		_pot *= _x;
		
	}
	
	return _y;
}
