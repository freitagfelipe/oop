#ifndef ALTERACAO_HPP
#define ALTERACAO_HPP

#include <vector>
#include <cmath>

std::vector<int> remove(const std::vector<int> &fila, int pos) {
    std::vector<int> resultado(fila);

    resultado.erase(resultado.begin() + pos);

    return resultado;
}

std::vector<int> insert(const std::vector<int> &fila, int valor, int pos) {
    std::vector<int> resultado(fila.begin(), fila.begin() + pos);

    resultado.push_back(valor);
    resultado.insert(resultado.end(), fila.begin() + pos, fila.end());

    return resultado;
}

std::vector<int> dance(const std::vector<int> &fila) {
    std::vector<int> resultado(fila);

    for (int i = 0; i < int(resultado.size()) - 1; i++) {
        if (std::abs(resultado.at(i)) == std::abs(resultado.at(i + 1))) {
            resultado.erase(resultado.begin() + i, resultado.begin() + i + 2);

            i = -1;
        }
    }

    return resultado;
}

#endif