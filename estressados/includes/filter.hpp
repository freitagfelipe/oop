#ifndef FILTER_HPP
#define FILTER_HPP

#include <vector>
#include <algorithm>
#include <iterator>

std::vector<int> clone(const std::vector<int> &fila) {
    return std::vector<int>(fila.begin(), fila.end());
}

std::vector<int> pegarHomens(const std::vector<int> &fila) {
    std::vector<int> auxiliar;
    std::copy_if(fila.begin(), fila.end(), std::back_inserter(auxiliar), [](int elemento) { return elemento > 0; });

    return auxiliar;
}

std::vector<int> pegarCalmos(const std::vector<int> &fila) {
    std::vector<int> auxiliar;
    std::copy_if(fila.begin(), fila.end(), std::back_inserter(auxiliar), [](int elemento) { return std::abs(elemento) < 10; });

    return auxiliar;
}

std::vector<int> pegarMulheresCalmas(const std::vector<int> &fila) {
    std::vector<int> auxiliar;
    std::copy_if(fila.begin(), fila.end(), std::back_inserter(auxiliar), [](int elemento) { return elemento > -10 && elemento < 0; });

    return auxiliar;
}

#endif