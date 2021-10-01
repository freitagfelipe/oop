#ifndef MELHORCASO_HPP
#define MELHORCASO_HPP

#include <vector>
#include <algorithm>

int procurarMenor(std::vector<int> fila) {
    return *std::min_element(fila.begin(), fila.end());
}

int procurarMenorPos(std::vector<int> fila) {
    std::vector<int>::iterator it = std::min_element(fila.begin(), fila.end());

    return std::distance(fila.begin(), it);
}

int procurarMenorPosApartir(std::vector<int> fila, int inicio) {
    std::vector<int> auxiliar(fila.begin() + inicio, fila.end());
    std::vector<int>::iterator it = std::min_element(auxiliar.begin(), auxiliar.end());
    
    return std::distance(auxiliar.begin(), it) + inicio;
}

int procurarMelhorSe(std::vector<int> fila) {
    int menor = 100;

    for (int estresse : fila) {
        if (estresse > 0 && estresse < menor) {
            menor = estresse;
        }
    }

    if (menor == 100) {
        return -1;
    }

    std::vector<int>::iterator it = std::find(fila.begin(), fila.end(), menor);

    return std::distance(fila.begin(), it);
}

#endif