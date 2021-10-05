#ifndef ACESSO_HPP
#define ACESSO_HPP

#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

std::vector<int> inverterComCopia(const std::vector<int> &fila) {
    std::vector<int> auxiliar(fila.begin(), fila.end());
    std::reverse(auxiliar.begin(), auxiliar.end());

    return auxiliar;
}

void inverterInplace(std::vector<int> &fila) {
    std::reverse(fila.begin(), fila.end());
}

int sortear(const std::vector<int> &fila) {
    std::srand(std::time(NULL));

    int sorteado = fila.at(rand() % (fila.size() - 1));

    return sorteado;
}

void embaralhar(std::vector<int> &fila) {
    std::random_shuffle(fila.begin(), fila.end());
}

void ordenar(std::vector<int> &fila) {
    std::sort(fila.begin(), fila.end());
}

#endif