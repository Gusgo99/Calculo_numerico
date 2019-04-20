#ifndef MATHIO_HPP
#define MATHIO_HPP

#include <functional>
#include <iterator>
#include <list>
#include <string>
#include <vector>

typedef std::pair<double, double> intervalo_t;

//															# # # Entrada de dados # # #

// Recebe uma funcao nas variaveis _vars do teclado e transforma essa string em uma funcao para o programa.
std::function<double(std::vector<double>)> ler_funcao(std::vector<std::string> _vars);
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Recebe uma funcao em RPN e retorna uma funcao que executa a funcao recebida
 * Ex: A funcao f(x) = x^2 + 3*x + 1 e equivalente em RPN a 
 * f(x) = x 2 ^ 3 x * 1 + +
 * Assim, se essa expressao for recebido, a funcao retornada calculara o valor
 * de f(x) no x recebido.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

//															# # # Saida de dados # # #

// Gera arquivo contendo dados para fazer grafico:
int gerar_grafico(std::string _nomeArquivo, std::list<std::pair<double, double>>::iterator _inicio, std::list<std::pair<double, double>>::iterator _fim);
// Overload para gerar grafico de uma funcao em um intervalo _I e com um passo _passo
int gerar_grafico(std::string _nomeArquivo, std::function<double(std::vector<double>)> f, intervalo_t _I, double _step);
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Pode-se desenhar o grafico gerado pela funcao com os comandos em R:
 * > dados <- read.table("Local do arquivo")
 * > plot(dados, type = "l")
 * O local do arquivo deve estar de acordo com o esperado pelo R:
 * Ex: "C:\\dados\\dados.dat"
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#endif
