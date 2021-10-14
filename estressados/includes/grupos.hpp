#ifndef GRUPOS_HPP
#define GRUPOS_HPP

#include <vector>
#include <cmath>
#include <map>

std::map<int, int> retornarMapa(const std::vector<int> &fila) {
    std::map<int, int> auxiliar;

    for (int estresse : fila) {
        int estresseAbsoluto = std::abs(estresse);

        if (auxiliar.find(estresseAbsoluto) == auxiliar.end()) {
            auxiliar[estresseAbsoluto] = 1;
        } else {
            auxiliar[estresseAbsoluto] += 1;
        }
    }

    return auxiliar;
}

int casais(const std::vector<int> &fila) {
    std::map<int, int> auxiliar = retornarMapa(fila);
    int resultado = 0;

    for (std::pair<int, int> pair : auxiliar) {
        resultado += pair.second / 2;
    }

    return resultado;
}

int trios(const std::vector<int> &fila) {
    std::map<int, int> auxiliar = retornarMapa(fila);
    int resultado = 0;

    for (std::pair<int, int> pair : auxiliar) {
        resultado += pair.second / 3;
    }

    return resultado;
}

#endif