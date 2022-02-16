#pragma once

#include <vector>
#include <algorithm>
#include <cstdlib>

std::vector<int> inverter_com_copia(const std::vector<int> &fila) {
    std::vector<int> auxiliar(fila.begin(), fila.end());
    std::reverse(auxiliar.begin(), auxiliar.end());

    return auxiliar;
}

void inverter_inplace(std::vector<int> &fila) {
    std::reverse(fila.begin(), fila.end());
}

int sortear(const std::vector<int> &fila) {
    int sorteado {fila.at(rand() % (fila.size() - 1))};

    return sorteado;
}

void embaralhar(std::vector<int> &fila) {
    std::random_shuffle(fila.begin(), fila.end(), [](int x) { return std::rand() % x; });
}

void ordenar(std::vector<int> &fila) {
    std::sort(fila.begin(), fila.end());
}