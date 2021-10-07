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
    std::vector<int>::iterator it = auxiliar.begin();

    for (int i = 0; i < fila.size(); i++) {
        if (std::find(fila.begin(), fila.end(), fila[i]) == auxiliar.end()) {
            int quantasVezesAparece = std::count(fila.begin(), fila.end(), fila[i]);

            auxiliar.insert(it, quantasVezesAparece - 1, fila[i]);

            it = auxiliar.begin() + auxiliar.size();
        }
    }

    return auxiliar;
}

#endif