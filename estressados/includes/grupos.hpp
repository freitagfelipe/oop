#ifndef GRUPOS_HPP
#define GRUPOS_HPP

#include <vector>
#include <cmath>
#include <map>

int casais(const std::vector<int> &fila) {
    std::map<int, int> homens, mulheres;
    int resultado = 0;

    for (int estresse : fila) {
        if (estresse > 0) {
            if (homens.find(estresse) == homens.end()) {
                homens[estresse] = 1;
            } else {
                homens[estresse] += 1;
            }
        } else {
            if (mulheres.find(estresse) == mulheres.end()) {
                mulheres[estresse] = 1;
            } else {
                mulheres[estresse] += 1;
            }
        }
    }

    for (std::pair<int, int> pair : homens) {
        int estresse = pair.first * -1;
        std::map<int, int>::iterator it = mulheres.find(estresse);

        if (it != mulheres.end()) {
            resultado += (pair.second + it->second) / 2;
        }
    }

    return resultado;
}

int trios(const std::vector<int> &fila) {
    std::map<int, int> auxiliar;
    int resultado = 0;

    for (int estresse : fila) {
        int estresseAbsoluto = std::abs(estresse);

        if (auxiliar.find(estresseAbsoluto) == auxiliar.end()) {
            auxiliar[estresseAbsoluto] = 1;
        } else {
            auxiliar[estresseAbsoluto] += 1;
        }
    }

    for (std::pair<int, int> pair : auxiliar) {
        resultado += pair.second / 3;
    }

    return resultado;
}

#endif