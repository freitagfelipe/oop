#pragma once

#include <vector>
#include <algorithm>

int procurar_menor(const std::vector<int> &fila) {
    return *std::min_element(fila.begin(), fila.end());
}

int procurar_menor_pos(const std::vector<int> &fila) {
    std::vector<int>::const_iterator it {std::min_element(fila.begin(), fila.end())};

    return std::distance(fila.begin(), it);
}

int procurar_menor_pos_apartir(const std::vector<int> &fila, int inicio) {
    std::vector<int>::const_iterator it {std::min_element(fila.begin() + inicio, fila.end())};
    
    return std::distance(fila.begin(), it);
}

int procurar_melhor_se(const std::vector<int> &fila) {
    int menor {100};

    for (int estresse : fila) {
        if (estresse > 0 && estresse < menor) {
            menor = estresse;
        }
    }

    if (menor == 100) {
        return -1;
    }

    std::vector<int>::const_iterator it {std::find(fila.begin(), fila.end(), menor)};

    return std::distance(fila.begin(), it);
}