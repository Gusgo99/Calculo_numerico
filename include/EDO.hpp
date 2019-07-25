#ifndef EDOS_HPP
#define EDOS_HPP

#include <functional>

typedef std::pair<double, double> intervalo_t;

std::function<double(double)> euler_EDO(std::function<double(double, double)> f, intervalo_t _I, double _a, double _passo);

#endif