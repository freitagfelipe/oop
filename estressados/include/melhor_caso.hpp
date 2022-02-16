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
    if (inicio < 0) {
        throw std::invalid_argument("A variável início deve ser maior ou igual a 0!");
    } else if (inicio >= int(fila.size())) {
        throw std::out_of_range("A variável início está ultrapassando o tamanho do vector!");
    }

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