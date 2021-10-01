#ifndef BUSCA_HPP
#define BUSCA_HPP

#include <vector>
#include <algorithm>

bool existe(std::vector<int> fila, int x) {
    return std::find(fila.begin(), fila.end(), x) == fila.end() ? false : true;
}

int contar(std::vector<int> fila, int x) {
    return std::count(fila.begin(), fila.end(), x);
}

int procurarValor(std::vector<int> fila, int x) {
    std::vector<int>::iterator it = std::find(fila.begin(), fila.end(), x);

    if (it != fila.end()) {
        int index = std::distance(fila.begin(), it);

        return index;
    }

    return -1;
}

int procurarValorApartir(std::vector<int> fila, int x, int inicio) {
    std::vector<int> auxiliar(fila.begin() + inicio, fila.end());
    std::vector<int>::iterator it = std::find(auxiliar.begin(), auxiliar.end(), x);

    if (it != fila.end()) {
        int index = std::distance(auxiliar.begin(), it);

        return index + inicio;
    }

    return -1;
}

#endif