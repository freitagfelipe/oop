#ifndef SEQUENCIAS_HPP
#define SEQUENCIAS_HPP

#include <vector>

enum Sexo { feminino, masculino };

int tamanhoDoTime(std::vector<int> &auxiliar, int tamanhoDoTimeAtual, Sexo sexoDoTimeAtual) {
    if (auxiliar.size() == 0) {
        return tamanhoDoTimeAtual;
    }

    Sexo sexoAtual = auxiliar.at(0) > 0 ? masculino : feminino;

    if (sexoAtual != sexoDoTimeAtual) {
        return tamanhoDoTimeAtual;
    }

    auxiliar.erase(auxiliar.begin());

    return tamanhoDoTime(auxiliar, tamanhoDoTimeAtual + 1, sexoDoTimeAtual);
}

int quantosTimes(const std::vector<int> &fila) {
    std::vector<int> auxiliar(fila);
    int resultado = 0;

    while (auxiliar.size()) {
        Sexo atual = auxiliar.at(0) > 0 ? masculino : feminino;

        int tamanhoDoTimeAtual = tamanhoDoTime(auxiliar, 0, atual);

        if (tamanhoDoTimeAtual > 1) {
            resultado++;
        }
    }

    return resultado;
}

int maiorTime(const std::vector<int> &fila) {
    std::vector<int> auxiliar(fila);
    int maiorTime = 0;

    while (auxiliar.size()) {
        Sexo atual = auxiliar.at(0) > 0 ? masculino : feminino;

        int tamanhoDoTimeAtual = tamanhoDoTime(auxiliar, 0, atual);

        if (tamanhoDoTimeAtual > 1 && tamanhoDoTimeAtual > maiorTime) {
            maiorTime = tamanhoDoTimeAtual;
        }
    }

    return maiorTime;
}

int sozinhosSequencia(const std::vector<int> &fila) {
    std::vector<int> auxiliar(fila);
    int sozinhos = 0;

    while (auxiliar.size()) {
        Sexo atual = auxiliar.at(0) > 0 ? masculino : feminino;

        int tamanhoDoTimeAtual = tamanhoDoTime(auxiliar, 0, atual);

        if (tamanhoDoTimeAtual == 1) {
            sozinhos++;
        }
    }

    return sozinhos;
}

#endif