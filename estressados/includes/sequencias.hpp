#pragma once

#include <vector>

enum class Sexo { feminino, masculino };

std::pair<int, int> tamanho_do_time(const std::vector<int> &fila, int tamanho_do_time_atual, Sexo sexo_do_time_atual, size_t index_atual) {
    if (fila.size() == index_atual) {
        return {tamanho_do_time_atual, index_atual};
    }

    Sexo sexo_atual {fila.at(index_atual) > 0 ? Sexo::masculino : Sexo::feminino};

    if (sexo_atual != sexo_do_time_atual) {
        return {tamanho_do_time_atual, index_atual};
    }

    return tamanho_do_time(fila, tamanho_do_time_atual + 1, sexo_do_time_atual, index_atual + 1);
}

int quantos_times(const std::vector<int> &fila) {
    int resultado {0};
    size_t index {0};

    while (index < fila.size()) {
        Sexo sexoAtual {fila.at(index) > 0 ? Sexo::masculino : Sexo::feminino};

        auto [tamanho_do_time_atual, index_atual] {tamanho_do_time(fila, 0, sexoAtual, index)};

        if (tamanho_do_time_atual > 1) {
            resultado++;
        }

        index = index_atual;
    }

    return resultado;
}

std::vector<int> maior_time(const std::vector<int> &fila) {
    std::vector<int> auxiliar;
    std::vector<int> resultado;
    Sexo time_atual {fila.at(0) > 0 ? Sexo::masculino : Sexo::feminino};

    for (size_t i {0}; i < fila.size(); ++i) {
        Sexo sexo_atual {fila.at(i) > 0 ? Sexo::masculino : Sexo::feminino};

        if (sexo_atual != time_atual) {
            time_atual = sexo_atual;

            if (auxiliar.size() > 1 && auxiliar.size() > resultado.size()) {
                resultado = auxiliar;
            }

            auxiliar.clear();
        }

        auxiliar.push_back(fila.at(i));
    }

    if (auxiliar.size() > 1 && auxiliar.size() > resultado.size()) {
        resultado = auxiliar;
    }

    return resultado;
}

int sem_time(const std::vector<int> &fila) {
    int sozinhos {0};
    size_t index {0};

    while (index < fila.size()) {
        Sexo sexo_atual {fila.at(index) > 0 ? Sexo::masculino : Sexo::feminino};

        auto [tamanho_do_time_atual, index_atual] {tamanho_do_time(fila, 0, sexo_atual, index)};

        if (tamanho_do_time_atual == 1) {
            sozinhos++;
        }

        index = index_atual;
    }

    return sozinhos;
}