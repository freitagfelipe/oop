#pragma once

#include <vector>
#include <cmath>

std::vector<int> remover(const std::vector<int> &fila, int pos) {
    if (pos < 0) {
        throw std::invalid_argument("A variável pos deve ser maior ou igual a 0!");
    } else if (pos >= int(fila.size())) {
        throw std::out_of_range("A variável pos está ultrapassando o tamanho do vector!");
    }

    std::vector<int> resultado(fila);

    resultado.erase(resultado.begin() + pos);

    return resultado;
}

std::vector<int> insert(const std::vector<int> &fila, int valor, int pos) {
    if (pos < 0) {
        throw std::invalid_argument("A variável pos deve ser maior ou igual a 0!");
    } else if (pos >= int(fila.size())) {
        throw std::out_of_range("A variável pos está ultrapassando o tamanho do vector!");
    }

    std::vector<int> resultado(fila);

    resultado.insert(resultado.begin() + pos, valor);

    return resultado;
}

std::vector<int> dance(const std::vector<int> &fila) {
    std::vector<int> resultado(fila);

    for (size_t i {0}; i < resultado.size() - 1; ++i) {
        if (std::abs(resultado.at(i)) == std::abs(resultado.at(i + 1))) {
            resultado.erase(resultado.begin() + i, resultado.begin() + i + 2);

            i = -1;
        }
    }

    return resultado;
}