#ifndef CONJUNTOS_HPP
#define CONJUNTOS_HPP

#include <vector>
#include <cmath>
#include <algorithm>
#include <set>

std::vector<int> exclusivos(const std::vector<int> &fila) {
    std::set<int> auxiliar(fila.begin(), fila.end());

    return std::vector<int>(auxiliar.begin(), auxiliar.end());
}

std::vector<int> diferentes(const std::vector<int> &fila) {
    for (int i : fila) {
        if (i < 0) {
            i = std::abs(i);
        }
    }

    std::set<int> auxiliar(fila.begin(), fila.end());

    return std::vector<int>(auxiliar.begin(), auxiliar.end());
}

std::vector<int> abandonados(const std::vector<int> &fila) {
    std::vector<int> auxiliar;

    std::copy_if(fila.begin(), fila.end(), std::back_inserter(auxiliar), [fila, &auxiliar](int elemento) { return (std::count(fila.begin(), fila.end(), elemento) > 1) && (std::find(auxiliar.begin(), auxiliar.end(), elemento) == auxiliar.end()); });

    return auxiliar;
}

#endif