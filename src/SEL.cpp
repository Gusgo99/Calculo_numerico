#include <algorithm>
#include <iostream>
#include <cmath>

#include "SEL.hpp"

class bad_equacao : public std::exception {
	public:
		const char* what() const noexcept {return "Tentativa de acesso a equacao nao existente\n";};
	
};

class bad_escalonamento : public std::exception {
	public:
		const char* what() const noexcept {return "A funcao resolve_escalonado recebeu um sistema escalonado um numero errado de equacoes\n";};
	
};

SEL::SEL(const size_t _vars) {
	vars = _vars;
	
	for(size_t i = 0; i != vars; i++) {
		equacoes.push_back({std::vector<double>(vars), 0});
		
	}
	
	return;
}

void SEL::mostrar_SEL() {
	for(size_t i = 0; i != vars; i++) {
		for(size_t j = 0; j != vars; j++) {
			std::cout << equacoes[i].first[j] << "*" << "x" << j << " ";
			if(j != vars - 1) {
				std::cout << "+ ";
				
			}
		}
		std::cout << "= " << equacoes[i].second << "\n";
	}
	
	return;
}

void SEL::receber_SEL() {
	for(size_t i = 0; i != vars; i++) {
		auto _temp = 0;
		for(size_t j = 0; j != vars; j++) {
			std::cin >> _temp;
			equacoes[i].first[j] = _temp;
			
		}
		std::cin >> _temp;
		equacoes[i].second = _temp;
	}
	
	return;
}

bool SEL::set_equacoes(const std::vector<std::pair<std::vector<double>, double>> &_equacoes) {
	for(auto i: _equacoes) {
		// Se o sistema recebido possuir um numero errado de equacoes ou coeficientes, da um throw
		if(i.first.size() != vars) {
			return false;
		}
	}
	equacoes = _equacoes;
	
	return true;
}

std::vector<std::pair<std::vector<double>, double>> SEL::get_equacoes() {
	return equacoes;
}

std::vector<double> SEL::calcular_residuo(const std::vector<double> &_estimativa) {
	std::vector<double> _residuo(vars);
	
	for(size_t i = 0; i != vars; i++) {
		_residuo[i] = equacoes[i].second;
		for(size_t j = 0; j != vars; j++) {
			_residuo[i] -= _estimativa[j] * equacoes[i].first[j];
			
		}
	}
	
	return _residuo;
}

void SEL::soma_linhas(const size_t _linha1, const size_t _linha2, const double _m) {
	if((_linha1 < vars) && (_linha2 < vars)) {
		for(size_t i = 0; i != vars; i++) {
			equacoes[_linha1].first[i] += _m * equacoes[_linha2].first[i];
			
		}
		equacoes[_linha1].second += _m * equacoes[_linha2].second;
		
	}
	else {
		throw bad_equacao();
		
	}
	
	return;
}

void SEL::abaixar_zeros(const size_t _inicio) {
	// Ordena equacoes iniciando da linha _inicio
	std::sort(equacoes.begin() + _inicio, equacoes.end(),
	[this](std::pair<std::vector<double>, double> a, std::pair<std::vector<double>, double> b) {
		for(size_t i = 0; i != vars; i++) {
			// Verifica de x0 ate xn qual coeficiente e igual a zero
			if((a.first[i] != b.first[i]) && (b.first[i] == 0)) {
				return true;
				
			}
		}
		
		return false;
	});
	
	return;
}

void SEL::dominantes(const size_t _inicio) {
	// Ordena linhas com base no maior coeficiente de cada linha
	std::sort(equacoes.begin() + _inicio, equacoes.end(),
	[this](std::pair<std::vector<double>, double> a, std::pair<std::vector<double>, double> b) {
		double _maiora = 0;
		double _maiorb = 0;
		for(size_t i = 0; i != vars; i++) {
			// Procura maior coeficiente na linha em valor absoluto
			if(fabs(a.first[i]) > _maiora) {
				_maiora = fabs(a.first[i]);
				
			}
			if(fabs(b.first[i]) > _maiorb) {
				_maiorb = fabs(b.first[i]);
				
			}
		}
		
		return _maiora > _maiorb;
	});
	
	return;
}

void SEL::tornar_principal_dominante() {
	// Ordena cada linha com base na variavel com maior coeficiente dentro da linha
	std::sort(equacoes.begin(), equacoes.end(),
	[this](std::pair<std::vector<double>, double> a, std::pair<std::vector<double>, double> b) {
		double _maiora = 0;
		double _maiorb = 0;
		
		for(size_t i = 0; i != vars; i++) {
			// Procura maior coeficiente da linha
			if(fabs(a.first[i]) > fabs(a.first[_maiora])) {
				_maiora = i;
				
			}
			if(fabs(b.first[i]) > fabs(b.first[_maiorb])) {
				_maiorb = i;
				
			}
		}
		
		return _maiora < _maiorb;
	});
	
	return;
}

std::vector<double> SEL::gauss_direto() {
	std::stack<std::pair<std::vector<double>, double>> _equacoes;
	std::stack<size_t> _var;
	
	// Executa escalonamento
	for(size_t i = 0; i != vars; i++) {
		// Evita que o coeficiente da linha analisada seja zero
		// Caso o valor seja zero, o sistema possui infinitas respostas
		abaixar_zeros(i);
		_equacoes.push(equacoes[i]);
		_var.push(i);
		for(auto j = (i + 1); j != vars; j++) {
			auto _m = equacoes[j].first[i] / equacoes[i].first[i];
			soma_linhas(j, i, -_m);
		
		}
	}
	
	// Retrodistribuicao
	return resolve_escalonado(_equacoes, _var);
}

std::vector<double> SEL::pivoteamento_completo() {
	std::stack<std::pair<std::vector<double>, double>> _equacoes;
	std::stack<size_t> _var;
	
	// Escalonamento
	for(size_t i = 0; i != vars; i++) {
		dominantes(i);
		auto _maior = std::distance(equacoes[i].first.begin(), std::max_element(equacoes[i].first.begin(), equacoes[i].first.end()));
		_equacoes.push(equacoes[i]);
		_var.push(_maior);
		for(size_t j = (i + 1); j != vars; j++) {
			auto _m = equacoes[j].first[_maior] / equacoes[i].first[_maior];
			soma_linhas(j, i, -_m);
			
		}
	}
	
	return resolve_escalonado(_equacoes, _var);
}

std::vector<double> SEL::resolve_escalonado(std::stack<std::pair<std::vector<double>, double>> &_sistema, std::stack<size_t> &_var) {
	std::vector<double> _solucao(vars);
	
	// Verifica se o numero de equacoes e variaveis estao corretos
	if((_sistema.size() != vars) || (_var.size() != vars)) {
		throw bad_escalonamento();
		
	}
	
	// Para cada equacao, calcula a respectiva componente da solucao
	while(!_sistema.empty()) {
		auto _temp = _sistema.top();
		_solucao[_var.top()] = _temp.second;
		for(size_t i = 0; i != vars; i++) {
			if(i != _var.top()) {
				_solucao[_var.top()] -= _solucao[i] * _temp.first[i];
				
			}
		}
		_solucao[_var.top()] /= _temp.first[_var.top()];
		_var.pop();
		_sistema.pop();
	}
	
	return _solucao;
}

std::vector<double> SEL::gauss_jacobi(const double _erro) {
	// Se nao for especificado o valor inicial, executa gauss_jacobi com o vetor inicial nulo
	return gauss_jacobi(std::vector<double> (vars), _erro);
}

std::vector<double> SEL::gauss_seidel(const double _erro) {
	// Se nao for especificado o valor inicial, executa gauss_seidel com o vetor inicial nulo
	return gauss_seidel(std::vector<double> (vars), _erro);
}

std::vector<double> SEL::gauss_jacobi(const std::vector<double> &_inicial, const double _erro) {
	// Solucao pela ultima iteracao e da iteracao atual
	std::vector<std::vector<double>> _solucoes = {std::vector<double> (vars), _inicial};
	// Erro da ultima iteracao
	double _erroAtual = 0;
	// Numero da iteracao
	size_t _it = 0;
	
	do {
		_erroAtual = 0;
		for(size_t i = 0; i != vars; i++) {
			// xn = (bn - an1*x1 - an2*x2 ...) / ann
			_solucoes[_it % 2][i] = equacoes[i].second;
			for(size_t j = 0; j != vars; j++) {
				if(i != j) {
					_solucoes[_it % 2][i] -= _solucoes[(_it + 1) % 2][j] * equacoes[i].first[j];
					
				}
			}
			_solucoes[_it % 2][i] /= equacoes[i].first[i];
			// Calcula erro atual
			_erroAtual = std::max(fabs(_solucoes[(_it + 1) % 2][i] - _solucoes[_it % 2][i]), _erroAtual);
			
		}
		
		// Se o numero de iteracoes ultrapassar o limite, para a execucao
		if(++_it > LIMIT_SEL) break;
		
	} while(_erroAtual > _erro);
	
	// Retorna ultima solucao calculada
	return _solucoes[(_it - 1) % 2];
}

// Similar a gauss_jacobi, porem utiliza os valores atualizados pela iteracao atual como solucao
std::vector<double> SEL::gauss_seidel(std::vector<double> _inicial, const double _erro) {
	// Erro da ultima iteracao
	double _erroAtual = 0;
	// Numero da iteracao
	size_t _it = 0;
	
	do {
		_erroAtual = 0;
		for(size_t i = 0; i != vars; i++) {
			auto _ant = _inicial[i];
			_inicial[i] = equacoes[i].second;
			for(size_t j = 0; j != vars; j++) {
				if(i != j) {
					_inicial[i] -= _inicial[j] * equacoes[i].first[j];
					
				}
			}
			_inicial[i] /= equacoes[i].first[i];
			_erroAtual = std::max(fabs(_ant - _inicial[i]), _erroAtual);
			
		}
		
		// Se o numero de iteracoes ultrapassar o limite, para a execucao
		if(++_it > LIMIT_SEL) break;
		
	} while(_erroAtual > _erro);
	
	return _inicial;
}
