#pragma once

#include <vector>
#include <cmath>
#include <map>

int casais(const std::vector<int> &fila) {
    std::map<int, int> homens, mulheres;

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

    int resultado {0};

    for (auto &[estresse, quantidade] : homens) {
        int estresse_mulher {estresse * -1};
        std::map<int, int>::iterator it {mulheres.find(estresse_mulher)};

        if (it != mulheres.end()) {
            resultado += (quantidade + it->second) / 2;
        }
    }

    return resultado;
}

int trios(const std::vector<int> &fila) {
    std::map<int, int> auxiliar;

    for (int estresse : fila) {
        int estresse_absoluto {std::abs(estresse)};

        if (auxiliar.find(estresse_absoluto) == auxiliar.end()) {
            auxiliar[estresse_absoluto] = 1;
        } else {
            auxiliar[estresse_absoluto] += 1;
        }
    }

    int resultado {0};

    for (auto &[estresse, quantidade] : auxiliar) {
        resultado += quantidade / 3;
    }

    return resultado;
}