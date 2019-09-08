#ifndef INTEGRACAO_HPP
#define INTEGRACAO_HPP

#include <utility>
#include <functional>

typedef std::pair<double, double> intervalo_t;

double trapezio(std::function<double(double)> f, intervalo_t _I, unsigned _divisoes);
double terco_simpson(std::function<double(double)> f, intervalo_t _I, unsigned _divisoes);

#endif