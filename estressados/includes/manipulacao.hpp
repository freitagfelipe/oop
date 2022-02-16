#pragma once

#include <vector>
#include <map>
#include <algorithm>

std::vector<int> sozinhos(const std::vector<int> &fila) {
    std::vector<int> auxiliar;

    for (int estresse : fila) {
        int estresse_atual {std::abs(estresse)};
        int quantas_vezes_aparece {int(std::count_if(fila.begin(), fila.end(), [estresse_atual](int x) { return std::abs(x) == estresse_atual; }))};

        if (quantas_vezes_aparece == 1) {
            auxiliar.push_back(estresse);
        }
    }

    return auxiliar;
}

int mais_ocorrencias(const std::vector<int> &fila) {
    int ocorrencias {0};

    for (int estresse : fila) {
        int quantas_vezes_aparece {int(std::count_if(fila.begin(), fila.end(), [estresse](int x) { return std::abs(x) == estresse; }))};

        if (quantas_vezes_aparece > ocorrencias) {
            ocorrencias = quantas_vezes_aparece;
        }
    }

    return ocorrencias;
}

std::vector<int> mais_recorrentes(const std::vector<int> &fila) {
    std::map<int, int> auxiliar;
    std::vector<int> resultado;
    int maior_numero_de_ocorrencias {mais_ocorrencias(fila)};

    for (int estresse : fila) {
        int estresse_absoluto {std::abs(estresse)};

        if (auxiliar.find(estresse_absoluto) == auxiliar.end()) {
            auxiliar[estresse_absoluto] = 1;
        } else {
            auxiliar[estresse_absoluto] += 1;
        }
    }

    for (auto &[estresse, quantidade] : auxiliar) {
        if (quantidade == maior_numero_de_ocorrencias) {
            resultado.push_back(estresse);
        }
    }

    return resultado;
}