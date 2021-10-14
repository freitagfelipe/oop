#ifndef MANIPULACAO_HPP
#define MANIPULACAO_HPP

#include <vector>
#include <map>
#include <algorithm>

std::vector<int> sozinhos(const std::vector<int> &fila) {
    std::vector<int> auxiliar;

    for (int estresse : fila) {
        int elementoAtual = std::abs(estresse);
        int quantasVezesAparece = std::count_if(fila.begin(), fila.end(), [elementoAtual](int x) { return std::abs(x) == elementoAtual; });

        if (quantasVezesAparece == 1) {
            auxiliar.push_back(elementoAtual);
        }
    }

    return auxiliar;
}

int maisOcorrencias(const std::vector<int> &fila) {
    int ocorrencias = 0;

    for (int estresse : fila) {
        int quantasVezesAparece = std::count_if(fila.begin(), fila.end(), [estresse](int x) { return std::abs(x) == estresse; });

        if (quantasVezesAparece > ocorrencias) {
            ocorrencias = quantasVezesAparece;
        }
    }

    return ocorrencias;
}

std::vector<int> maisRecorrentes(const std::vector<int> &fila) {
    std::map<int, int> auxiliar;
    std::vector<int> resultado;
    int maiorNumeroDeOcorrencias = maisOcorrencias(fila);

    for (int estresse : fila) {
        int estresseAbsoluto = std::abs(estresse);

        if (auxiliar.find(estresseAbsoluto) == auxiliar.end()) {
            auxiliar[estresseAbsoluto] = 1;
        } else {
            auxiliar[estresseAbsoluto] += 1;
        }
    }

    for (std::pair<int, int> pair : auxiliar) {
        if (pair.second == maiorNumeroDeOcorrencias) {
            resultado.push_back(pair.first);
        }
    }

    return resultado;
}

#endif