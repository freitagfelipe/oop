#pragma once

#include <vector>
#include <numeric>

double calcular_stress_medio(const std::vector<int> &fila) {
    double estresse {0};

    for (int estresse_atual : fila) {
        estresse += std::abs(estresse_atual);
    }

    return estresse / fila.size();
}

std::string mais_homens_ou_mulheres(const std::vector<int> &fila) {
    int homens {0}, mulheres {0};

    for (int estresse : fila) {
        if (estresse < 0) {
            mulheres++;
        } else {
            homens++;
        }
    }

    return homens > mulheres ? "homens" : homens == mulheres ? "empate" : "mulheres";
}

std::string qual_metade_eh_mais_estressada(std::vector<int> fila) {
    if (fila.size() % 2 != 0) {
        std::vector<int>::iterator it {fila.begin() + fila.size() / 2};
        
        fila.erase(it);
    }

    for (int &estresse : fila) {
        estresse = std::abs(estresse);
    }

    int esquerda {std::accumulate(fila.begin(), fila.end() - fila.size() / 2, 0)};
    int direita {std::accumulate(fila.begin() + fila.size() / 2, fila.end(), 0)};

    return esquerda > direita ? "primeira" : direita == esquerda ? "empate" : "segunda";
}

bool homens_sao_mais_estressados(const std::vector<int> &fila) {
    int homens {0}, mulheres {0};

    for (int estresse : fila) {
        if (estresse < 0) {
            mulheres += estresse;
        } else {
            homens += estresse;
        }
    }

    return homens > std::abs(mulheres);
}