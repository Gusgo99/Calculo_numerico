#ifndef ZEROS_HPP
#define ZEROS_HPP

// LIMite de ITeracoes
const uint32_t LIMIT = 1000;

//#define COMPARAR

#include <list>
#include <utility>

typedef std::pair<double, double> intervalo_t;

// Vasculha o intervalor _I para encontrar intervalos que contenham zeros
std::list<intervalo_t> encontra_intervalos(double (*f)(double), intervalo_t _I, double _step);
// Metodo da bisseccao para aproximacao de zeros
double bisseccao(double (*f)(double), intervalo_t _I, double _erro);
// Metodo do ponto fixo para aproximacao de zeros
double ponto_fixo(double (*f)(double), double (*fi)(double), intervalo_t _I, double _erro);
// Metodo da tangente para aproximacao de zeros
double tangente(double (*f)(double), double (*dfdx)(double), intervalo_t _I, double _erro);
// Metodo da secante para aproximacao de zeros
double secante(double (*f)(double), intervalo_t _I, double _erro);

#endif