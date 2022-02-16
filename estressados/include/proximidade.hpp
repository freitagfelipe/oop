#pragma once

#include <vector>
#include <cmath>

int briga(const std::vector<int> &fila) {
    int resultado {0};

    for (size_t i {1}; i < fila.size() - 1; ++i) {
        if (std::abs(fila.at(i)) > 50 && std::abs(fila.at(i - 1)) > 30 && std::abs(fila.at(i + 1)) > 30) {
            resultado++;
        }
    }

    return resultado;
}

std::vector<int> apaziguado(const std::vector<int> &fila) {
    std::vector<int> resultado;

    for (size_t i {0}; i < fila.size(); ++i) {
        if (std::abs(fila.at(i)) > 80) {
            bool apaziguado {false};

            if (i > 0 && std::abs(fila.at(i - 1)) < 10) {
                apaziguado = true;
            } else if (i < fila.size() - 1 && std::abs(fila.at(i + 1)) < 10) {
                apaziguado = true;
            }

            if (apaziguado) {
                resultado.push_back(i);
            }
        }
    }

    return resultado;
}