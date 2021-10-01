#ifndef CONTAGEM_HPP
#define CONTAGEM_HPP

#include <iostream>
#include <vector>
#include <numeric>

float calcularStressMedio(std::vector<int> fila) {
    for (int &estresse : fila) {
        estresse = std::abs(estresse);
    }

    return (float) std::accumulate(fila.begin(), fila.end(), 0) / fila.size();
}

std::string maisHomensOuMulheres(std::vector<int> fila) {
    int homens = 0, mulheres = 0;

    for (int estresse : fila) {
        if (estresse < 0) {
            mulheres++;
        } else {
            homens++;
        }
    }

    return homens > mulheres ? "homens" : homens == mulheres ? "empate" : "mulheres";
}

std::string qualMetadeEhMaisEstressada(std::vector<int> fila) {
    if (fila.size() % 2 != 0) {
        std::vector<int>::iterator it = fila.begin() + fila.size() / 2;
        
        fila.erase(it);
    }

    for (int &estresse : fila) {
        estresse = std::abs(estresse);
    }

    int esquerda = std::accumulate(fila.begin(), fila.end() - fila.size() / 2, 0);
    int direita = std::accumulate(fila.begin() + fila.size() / 2, fila.end(), 0);

    return esquerda > direita ? "primeira" : direita == esquerda ? "empate" : "segunda";
}

bool homensSaoMaisEstressadosQueMulheres(std::vector<int> fila) {
    int homens = 0, mulheres = 0;

    for (int estresse : fila) {
        if (estresse < 0) {
            mulheres += estresse;
        } else {
            homens += estresse;
        }
    }

    return homens > true;
}

#endif