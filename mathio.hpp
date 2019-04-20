#ifndef MATHIO_HPP
#define MATHIO_HPP

#include <functional>
#include <string>
#include <vector>

// Recebe uma funcao nas variaveis _vars do teclado e transforma essa string em uma funcao para o programa.
std::function<double(std::vector<double>)> ler_funcao(std::vector<std::string> _vars);

#endif
