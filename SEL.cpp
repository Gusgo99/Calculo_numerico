#include <iostream>
#include <cmath>
#include <stack>

#include "SEL.hpp"

// Metodo de Gauss para resolver SEL.
// Nao verifica se o sistema e possivel ou se ele possui resposta unica.
std::vector<double> gauss_sel(SEL _sel) {
	double _m;
	std::vector<double> _solucoes;
	
	// Executa escalonamento
	for(auto i = 0; i != _sel.size(); i++) {
		_solucoes.push_back(0);
		// Se o pivo de uma linha for nulo, troca a linha.
		for(auto j = (i + 1); j != _sel.size(); j++) {
			for(auto k = 0; (_sel[i][i] == 0) && ((i + k) != _sel.size()); k++) {
				auto _aux = _sel[i + k];
				_sel[i + k] = _sel[i];
				_sel[i] = _aux;
				
			}
			_m = _sel[j][i] / _sel[i][i];
			// Soma linha com o oposto do multiplicador
			for(auto k = 0; k != _sel[j].size(); k++) {
				_sel[j][k] -= _m * _sel[i][k];
				
			}
		}
	}
	
	auto _it = _sel.end();
	_it--;
	
	// Calcula valor de cada variavel
	for(auto i = (_sel.size() - 1); i != -1; i--) {
		auto _soma = 0.00;
		for(auto j = (i + 1); j < _sel.size(); j++) {
			_soma += (*_it)[j] * _solucoes[j];
			
		}
		_solucoes[i] = ((*_it)[_sel.size()] - _soma) / (*_it)[i];
		_it--;
		
	}
	
	return _solucoes;
}
