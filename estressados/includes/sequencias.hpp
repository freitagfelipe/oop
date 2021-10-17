#ifndef SEQUENCIAS_HPP
#define SEQUENCIAS_HPP

#include <vector>

enum Sexo { feminino, masculino };

int tamanhoDoTime(std::vector<int> &fila, int tamanhoDoTimeAtual, Sexo sexoDoTimeAtual) {
    if (fila.size() == 0) {
        return tamanhoDoTimeAtual;
    }

    Sexo sexoAtual = fila.at(0) > 0 ? masculino : feminino;

    if (sexoAtual != sexoDoTimeAtual) {
        return tamanhoDoTimeAtual;
    }

    fila.erase(fila.begin());

    return tamanhoDoTime(fila, tamanhoDoTimeAtual + 1, sexoDoTimeAtual);
}

int quantosTimes(const std::vector<int> &fila) {
    std::vector<int> copia(fila);
    int resultado = 0;

    while (copia.size()) {
        Sexo sexoAtual = copia.at(0) > 0 ? masculino : feminino;

        int tamanhoDoTimeAtual = tamanhoDoTime(copia, 0, sexoAtual);

        if (tamanhoDoTimeAtual > 1) {
            resultado++;
        }
    }

    return resultado;
}

std::vector<int> maiorTime(const std::vector<int> &fila) {
    std::vector<int> auxiliar;
    std::vector<int> resultado;
    Sexo timeAtual = fila.at(0) > 0 ? masculino : feminino;

    for (int i = 0; i < int(fila.size()); i++) {
        Sexo sexoAtual = fila.at(i) > 0 ? masculino : feminino;

        if (sexoAtual != timeAtual || i == int(fila.size()) - 1) {
            timeAtual = sexoAtual;

            if (auxiliar.size() > 1 && auxiliar.size() > resultado.size()) {
                resultado = auxiliar;
            }

            auxiliar.clear();

            auxiliar.push_back(fila.at(i));
        } else {
            auxiliar.push_back(fila.at(i));
        }
    }

    return resultado;
}

int sozinhosSequencia(const std::vector<int> &fila) {
    std::vector<int> copia(fila);
    int sozinhos = 0;

    while (copia.size()) {
        Sexo sexoAtual = copia.at(0) > 0 ? masculino : feminino;

        int tamanhoDoTimeAtual = tamanhoDoTime(copia, 0, sexoAtual);

        if (tamanhoDoTimeAtual == 1) {
            sozinhos++;
        }
    }

    return sozinhos;
}

#endif