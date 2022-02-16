#pragma once

#include <vector>
#include <algorithm>
#include <iterator>

std::vector<int> clone(const std::vector<int> &fila) {
    return std::vector<int>(fila.begin(), fila.end());
}

std::vector<int> pegar_homens(const std::vector<int> &fila) {
    std::vector<int> auxiliar;
    std::copy_if(fila.begin(), fila.end(), std::back_inserter(auxiliar), [](int estresse) { return estresse > 0; });

    return auxiliar;
}

std::vector<int> pegar_calmos(const std::vector<int> &fila) {
    std::vector<int> auxiliar;
    std::copy_if(fila.begin(), fila.end(), std::back_inserter(auxiliar), [](int estresse) { return std::abs(estresse) < 10; });

    return auxiliar;
}

std::vector<int> pegar_mulheres_calmas(const std::vector<int> &fila) {
    std::vector<int> auxiliar;
    std::copy_if(fila.begin(), fila.end(), std::back_inserter(auxiliar), [](int estresse) { return estresse > -10 && estresse < 0; });

    return auxiliar;
}