#ifndef MATHIO_HPP
#define MATHIO_HPP

#include <functional>
#include <string>
#include <vector>
#include <iterator>

// # # # Entrada de dados # # #

// Recebe uma funcao nas variaveis _vars do teclado e transforma essa string em uma funcao para o programa.
std::function<double(std::vector<double>)> ler_funcao(std::vector<std::string> _vars);

// # # # Saida de dados # # #

// Gera arquivo contendo dados para fazer grafico:
int gerar_grafico(std::string _nomeArquivo, std::list<std::pair<double, double>>::iterator _inicio, std::list<std::pair<double, double>>::iterator _fim);
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Pode-se desenhar o grafico gerado pela funcao com os comandos em R:
 * > dados <- read.table("Local do arquivo")
 * > plot(dados, type = "l")
 * O local do arquivo deve estar de acordo com o esperado pelo R:
 * Ex: "C:\\dados\\dados.dat"
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#endif
