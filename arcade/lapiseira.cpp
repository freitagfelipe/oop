#include <iostream>
#include <sstream>
#include <memory>
#include <list>

class Grafite {
public:
    Grafite(double calibre, std::string dureza, int tamanho) {
        this->calibre = calibre;
        this->dureza = dureza;
        this->tamanho = tamanho;
    }

    int desgaste_por_folha() {
        if (this->dureza == "HB") {
            return 1;
        } else if (this->dureza == "2B") {
            return 2;
        } else if (this->dureza == "4B") {
            return 4;
        } else {
            return  6;
        }
    }

    double get_calibre() const {
        return this->calibre;
    }

    std::string to_string() const {
        std::stringstream ss;

        ss << this->calibre << ":" << this->dureza << ":" << this->tamanho;

        return ss.str();
    }

    bool gastar_grafite() {
        if (this->tamanho - this->desgaste_por_folha() < 10) {
            this->tamanho = 10;

            return false;
        }

        this->tamanho -= this->desgaste_por_folha();

        return true;
    }

    int get_tamanho() const {
        return this->tamanho;
    }

private:
    double calibre;
    std::string dureza;
    int tamanho;
};

class Lapiseira {
public:
    Lapiseira(double calibre) {
        this->calibre = calibre;
        this->bico = nullptr;
    }

    bool inserir(std::shared_ptr<Grafite> grafite) {
        if (grafite->get_calibre() == this->calibre) {
            this->tambor.push_back(grafite);

            return true;
        }

        std::cout << "Calibre incorreto!" << std::endl;

        return false;
    }

    bool puxar_grafite() {
        if (bico != nullptr) {
            std::cout << "Já existe uma grafite no bico!" << std::endl;

            return false;
        }

        if (this->tambor.size() == 0) {
            std::cout << "O tambor está vazio!" << std::endl;

            return false;
        }

        this->bico = this->tambor.front();
        this->tambor.pop_front();

        return true;
    }

    std::shared_ptr<Grafite> remover() {
        return std::exchange(this->bico, nullptr);
    }

    void escrever() {
        if (this->bico == nullptr) {
            std::cout << "Não existe grafite no bico!" << std::endl;

            return;
        } else if (this->bico->get_tamanho() == 10) {
            std::cout << "Grafite acabou!" << std::endl;

            return;
        }

        if (!this->bico->gastar_grafite()) {
            std::cout << "Folha incompleta!" << std::endl;
        }

        if (this->bico->get_tamanho() == 10) {
            std::cout << "Grafite acabou!" << std::endl;
        }
    }

    std::string to_string() const {
        std::stringstream ss;

        if (this->bico != nullptr) {
            ss << "calibre: " << this->calibre << ", bico: [" << this->bico->to_string() << "], tambor: {";
        } else {
            ss << "calibre: " << this->calibre << ", bico: [], tambor: {";
        }
        
        
        for (const std::shared_ptr<Grafite> &grafite : this->tambor) {
            ss << "[" << grafite->to_string() << "]";
        }

        ss << "}";

        return ss.str();
    }

private:
    std::shared_ptr<Grafite> bico;
    double calibre;
    std::list<std::shared_ptr<Grafite>> tambor;
};

int main() {
    
    return 0;
}