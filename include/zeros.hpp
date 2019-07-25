#ifndef ZEROS_HPP
#define ZEROS_HPP

// LIMite de ITeracoes
const uint32_t LIMIT = 1000;

#define COMPARAR

#include <list>
#include <utility>
#include <functional>

typedef std::pair<double, double> intervalo_t;

// Vasculha o intervalor _I para encontrar intervalos que contenham zeros
std::list<intervalo_t> encontra_intervalos(std::function<double(double)> f, intervalo_t _I, double _step);

// Metodo da bisseccao para aproximacao de zeros
double bisseccao(std::function<double(double)> f, intervalo_t _I, double _erro);
// Metodo do ponto fixo para aproximacao de zeros
double ponto_fixo(std::function<double(double)> f, std::function<double(double)> fi, intervalo_t _I, double _erro);
// Metodo da tangente para aproximacao de zeros
double tangente(std::function<double(double)> f, std::function<double(double)> dfdx, intervalo_t _I, double _erro);
// Metodo da secante para aproximacao de zeros
double secante(std::function<double(double)> f, intervalo_t _I, double _erro);

#endif
