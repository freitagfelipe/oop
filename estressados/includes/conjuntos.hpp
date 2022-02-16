#pragma once

#include <vector>
#include <cmath>
#include <algorithm>
#include <set>

std::vector<int> exclusivos(const std::vector<int> &fila) {
    std::set<int> auxiliar(fila.begin(), fila.end());

    return std::vector<int>(auxiliar.begin(), auxiliar.end());
}

std::vector<int> diferentes(const std::vector<int> &fila) {
    std::set<int> auxiliar;

    for (int i : fila) {
        auxiliar.insert(std::abs(i));
    }

    return std::vector<int>(auxiliar.begin(), auxiliar.end());
}

std::vector<int> abandonados(const std::vector<int> &fila) {
    std::vector<int> auxiliar;

    for (size_t i {0}; i < fila.size(); ++i) {
        if (std::find(auxiliar.begin(), auxiliar.end(), fila.at(i)) == auxiliar.end()) {
            int quantas_vezes_aparece {int(std::count(fila.begin(), fila.end(), fila.at(i)))};

            auxiliar.insert(auxiliar.end(), quantas_vezes_aparece - 1, fila.at(i));
        }
    }

    return auxiliar;
}