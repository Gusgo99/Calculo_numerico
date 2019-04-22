#include <cmath>
#include <cstdarg>
#include <fstream>
#include <iostream>
#include <queue>
#include <stack>
#include <utility>
#include <fstream>

#include <list>

#include "mathio.hpp"

// Constantes matematicas
const double PI = acos(-1);
const double e = exp(1);
const double TAU = 2 * PI;

// Texto para cada operacao implementada:
const std::array<std::string, 25> OPS = {
	"+", "-", "*", "/", "^",	// 5
	"sin", "asin", "cos", "acos", "tg", "atg", // 6
	"sinh", "asinh", "cosh", "acosh", "tgh", "atgh", // 6
	"sqrt", "log", "ln", "exp", "abs", // 5
	"tau", "pi", "e"}; // 3
	
// Elementos a serem adicionados quando a respectiva operacao em OPS for realizada (-1 indica que a pilha tera 1 elemento a menos):
const std::array<int, 25> EFEITO = {
	-1, -1, -1, -1, -1,
	0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	1, 1, 1};

// Diferentes tipos de operacao em uma stack.(Adicionar numero no topo, realizar operacao matematica e adicionar valor de variavel no topo)
enum {NUM, OP, VAR};

union tipoDado_u {
	double num;
	uint64_t op;
	uint64_t var;
	
};

// Cada operacao em RPN tem dois valores, o primeiro indica qual o segundo dado. O segundo dado pode ser um numero, operacao ou variavel.
// Caso o segundo dado seja um numero, isso significa que esse numero deve ser adicionado a stack.
// Caso o segundo dado  seja uma operacao, a operacao deve ser realizada com os numeros no topo da stack.
// Caso o segundo dado seja uma variavel, o valor da variavel deve ser adicionada a stack.
typedef std::queue<std::pair<uint8_t, tipoDado_u>> fRPN_t;

// Calcula resultado de uma funcao calculada em _args. Funcao descrita por _RPN.
double executar_operacoes(fRPN_t _RPN, std::vector<double> _args);
// Calcula o resultado de uma unica operacao na pilha.
void operacao_stack(std::stack<double> *_pilha, uint64_t _op);

// # # # Definicao das funcoes # # #

std::function<double(std::vector<double>)> ler_funcao(std::vector<std::string> _vars) {
	fRPN_t _funcao;					// Descricao da funcao em RPN
	tipoDado_u _temp;
	std::string _entrada;
	int _numArgs = _vars.size();
	int _prof = 0;					// Acumula quantos elementos a stack possui
	
	std::cout << "f(";
	for(auto i = 0; i != _vars.size(); i++) {
		std::cout << _vars[i];
		if(i != (_vars.size() - 1)) {
			std::cout << ", ";
			
		}
	}
	std::cout << ") = ";
	
	// Solucao temporaria:
	fflush(stdin);
	
	while(std::cin.peek() != '\n') {
		// Descarta espacos: 
		if(std::cin.peek() == ' ') {
			std::cin.get();
			continue;
		}
		
		std::cin >> _entrada;
		
		// Verifica se o valor inserido e um numero:
		if(isdigit(_entrada[0]) || (_entrada[0] == '-' && isdigit(_entrada[1]))) {
			_temp.num = stod(_entrada);
			_funcao.push(std::pair(NUM, _temp));
			_prof++;
			
		}
		else {
			// Verifica se a entrada analisada e uma operacao:
			for(auto i = 0; i != OPS.size(); i++) {
				if(_entrada == OPS[i]) {
					_temp.op = i;
					_funcao.push(std::pair(OP, _temp));
					_prof += EFEITO[i];
					break;
					
				}
			}
			// Verifica se a entrada analisada e uma variavel:
			for(auto i = 0; i != _vars.size(); i++) {
				if(_entrada == _vars[i]) {
					_temp.var = i;
					_funcao.push(std::pair(VAR, _temp));
					_prof++;
					break;
					
				}
			}
		}
		// Verifica se a ultima operacao nao utiliza elementos que nao estao na stack:
		if(_prof <= 0) return nullptr;
	}
	
	// Funcao lambda que calcula a funcao no ponto definido por _args:
	return [_funcao](std::vector<double> _args) {
		return executar_operacoes(_funcao, _args);
	};
}

double executar_operacoes(fRPN_t _RPN, std::vector<double> _args) {
	std::stack<double> _pilha;
	
	// Executa cada passo descrito por _RPN:
	while(_RPN.size() > 0) {
		// Passo atual:
		auto i = _RPN.front();
		_RPN.pop();
		// Verifica se o passo atual manda adicionar um numero a stack:
		if(i.first == NUM) {
			_pilha.push(i.second.num);
			
		}
		// Verifica se o passo atual e uma operacao matematica:
		else if(i.first == OP) {
			operacao_stack(&_pilha, i.second.op);
			
		}
		// Verifica se o passo atual e adicionar o valor de uma variavel a pilha:
		else if(i.first == VAR) {
			_pilha.push(_args[i.second.var]);
			
		}
	}
	
	// Retorna o que esta no topo da pilha
	return _pilha.top();
}

void operacao_stack(std::stack<double> *_pilha, uint64_t _op) {
	double a, b;
	
	// Executa a respectiva operacao(O numero e definido pela posicao da operacao no array OPS):
	switch(_op) {
		case 0:				// "+"
			a = _pilha -> top();
			_pilha -> pop();
			b = _pilha -> top();
			_pilha -> pop();
			_pilha -> push(a + b);
			break;
			
		case 1:				// "-"
			a = _pilha -> top();
			_pilha -> pop();
			b = _pilha -> top();
			_pilha -> pop();
			_pilha -> push(b - a);
			break;
			
		case 2:				// "*"
			a = _pilha -> top();
			_pilha -> pop();
			b = _pilha -> top();
			_pilha -> pop();
			_pilha -> push(a * b);
			break;
			
		case 3:				// "/"
			a = _pilha -> top();
			_pilha -> pop();
			b = _pilha -> top();
			_pilha -> pop();
			_pilha -> push(b / a);
			break;
			
		case 4:				// "^"
			a = _pilha -> top();
			_pilha -> pop();
			b = _pilha -> top();
			_pilha -> pop();
			_pilha -> push(pow(b, a));
			break;
			
		case 5:				// "sin"
			a = _pilha -> top();
			_pilha -> pop();
			_pilha -> push(sin(a));
			break;
			
		case 6:				// "asin"
			a = _pilha -> top();
			_pilha -> pop();
			_pilha -> push(asin(a));
			break;
			
		case 7:				// "cos"
			a = _pilha -> top();
			_pilha -> pop();
			_pilha -> push(cos(a));
			break;
			
		case 8:				// "acos"
			a = _pilha -> top();
			_pilha -> pop();
			_pilha -> push(acos(a));
			break;
			
		case 9:				// "tg"
			a = _pilha -> top();
			_pilha -> pop();
			_pilha -> push(tan(a));
			break;
			
		case 10:				// "atg"
			a = _pilha -> top();
			_pilha -> pop();
			_pilha -> push(atan(a));
			break;
			
		case 11:				// "sinh"
			a = _pilha -> top();
			_pilha -> pop();
			_pilha -> push(sinh(a));
			break;
			
		case 12:				// "asinh"
			a = _pilha -> top();
			_pilha -> pop();
			_pilha -> push(asinh(a));
			break;
			
		case 13:				// "cosh"
			a = _pilha -> top();
			_pilha -> pop();
			_pilha -> push(cosh(a));
			break;
			
		case 14:				// "acosh"
			a = _pilha -> top();
			_pilha -> pop();
			_pilha -> push(acosh(a));
			break;
			
		case 15:				// "tgh"
			a = _pilha -> top();
			_pilha -> pop();
			_pilha -> push(tanh(a));
			break;
			
		case 16:				// "atgh"
			a = _pilha -> top();
			_pilha -> pop();
			_pilha -> push(atanh(a));
			break;
			
		case 17:				// "sqrt"
			a = _pilha -> top();
			_pilha -> pop();
			_pilha -> push(sqrt(a));
			break;
			
		case 18:				// "log"
			a = _pilha -> top();
			_pilha -> pop();
			_pilha -> push(log10(a));
			break;
			
		case 19:				// "ln"
			a = _pilha -> top();
			_pilha -> pop();
			_pilha -> push(log(a));
			break;
			
		case 20:				// "exp"
			a = _pilha -> top();
			_pilha -> pop();
			_pilha -> push(exp(a));
			break;
			
		case 21:				// "abs"
			a = _pilha -> top();
			_pilha -> pop();
			_pilha -> push(fabs(a));
			break;
			
			// Operacoes tau, pi e e sao utilizadas para adicionar elemento na lista
		case 22:				// "tau"
			_pilha -> push(TAU);
			break;
			
		case 23:				// "pi"
			_pilha -> push(PI);
			break;
			
		case 24:				// "e"
			_pilha -> push(e);
			break;
			
	}
	
	return;
}

int gerar_grafico(std::string _nomeArquivo, std::list<std::pair<double, double>>::iterator _inicio, std::list<std::pair<double, double>>::iterator _fim) {
	std::ofstream _arquivo(_nomeArquivo);
	
	if(_arquivo.is_open()) {
		while(_inicio != _fim) {
			_arquivo << _inicio -> first << "\t" << _inicio -> second << std::endl;
			_inicio++;
			
		}
	}
	else {
		return EXIT_FAILURE;
		
	}
	
	return EXIT_SUCCESS;
}

int gerar_grafico(std::string _nomeArquivo, std::function<double(std::vector<double>)> f, intervalo_t _I, double _step) {
	std::list<std::pair<double, double>> _lista;
	
	for(auto i = _I.first; i < _I.second; i += _step) {
		_lista.push_back(std::pair(i, f({i})));
		
	}
	
	return gerar_grafico(_nomeArquivo, _lista.begin(), _lista.end());
}
