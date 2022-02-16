#pragma once

#include <vector>
#include <algorithm>

bool existe(const std::vector<int> &fila, int x) {
    return std::find(fila.begin(), fila.end(), x) == fila.end() ? false : true;
}

int contar(const std::vector<int> &fila, int x) {
    return std::count(fila.begin(), fila.end(), x);
}

int procurar_valor(const std::vector<int> &fila, int x) {
    std::vector<int>::const_iterator it {std::find(fila.begin(), fila.end(), x)};

    if (it != fila.end()) {
        int index {int(std::distance(fila.begin(), it))};

        return index;
    }

    return -1;
}

int procurar_valor_a_partir(const std::vector<int> &fila, int x, int inicio) {
    std::vector<int>::const_iterator it {std::find(fila.begin() + inicio, fila.end(), x)};

    if (it != fila.end()) {
        int index {int(std::distance(fila.begin(), it))};

        return index;
    }

    return -1;
}