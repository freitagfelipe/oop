#ifndef PROXIMIDADE_HPP
#define PROXIMIDADE_HPP

#include <vector>
#include <cmath>

int briga(const std::vector<int> &fila) {
    int resultado = 0;

    for (int i = 1; i < int(fila.size()) - 1; i++) {
        if (std::abs(fila.at(i)) > 50 && std::abs(fila.at(i - 1)) > 30 && std::abs(fila.at(i + 1)) > 30) {
            resultado++;
        }
    }

    return resultado;
}

std::vector<int> apaziguado(const std::vector<int> &fila) {
    std::vector<int> resultado;

    for (int i = 0; i < int(fila.size()); i++) {
        if (fila.at(i) > 80) {
            bool apaziguado = false;

            if (i > 0 && std::abs(fila.at(i - 1)) < 10) {
                apaziguado = true;
            } else if (i < int(fila.size() - 1) && std::abs(fila.at(i + 1)) < 10) {
                apaziguado = true;
            }

            if (apaziguado) {
                resultado.push_back(i);
            }
        }
    }

    return resultado;
}

#endif