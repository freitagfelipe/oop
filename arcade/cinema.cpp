#include <iostream>
#include <sstream>
#include <memory>
#include <vector>

class Client {
public:
    Client(std::string name, std::string phone) {
        this->name = name;
        this->phone = phone;
    }

    std::string to_string() const {
        std::stringstream ss;

        ss << this->name << ":" << this->phone;

        return ss.str();
    }

    std::string get_phone() const {
        return this->phone;
    }

    void set_phone(std::string phone) {
        this->phone = phone;
    }

    std::string get_name() const {
        return this->name;
    }

    void set_name(std::string name) {
        this->name = name;
    }

private:
    std::string name;
    std::string phone;
};

class MovieTheater {
public:
    MovieTheater(int how_many_chairs) {
        this->how_many_chairs = how_many_chairs;
        this->chairs.resize(how_many_chairs, nullptr);
    }

    void cancel(std::string name) {
        for (std::vector<std::shared_ptr<Client>>::iterator it {this->chairs.begin()}; it != this->chairs.end(); ++it) {
            if (*it != nullptr && it->get()->get_name() == name) {
                *it = nullptr;

                return;
            }
        }

        std::cout << "Cliente não está no cinema!" << std::endl;
    }

    bool reserve(std::string name, std::string phone, int chair_number) {
        if (chair_number < 0 || chair_number >= this->how_many_chairs) {
            std::cout << "Escolha uma cadeira válida!" << std::endl;

            return false;
        }

        for (const std::shared_ptr<Client> &client : this->chairs) {
            if (client != nullptr && client->get_name() == name) {
                std::cout << "Cliente já está no cinema!" << std::endl;

                return false;
            }
        }

        if (this->chairs.at(chair_number) == nullptr) {
            this->chairs.at(chair_number) = std::make_shared<Client>(name, phone);

            return true;
        }

        std::cout << "Cadeira já reservada!" << std::endl;

        return false;
    }

    std::vector<std::shared_ptr<Client>>& get_chairs() {
        return this->chairs;
    }

    std::string to_string() const {
        std::stringstream ss;

        ss << "[";

        for (const std::shared_ptr<Client> &client : chairs) {
            if (client != nullptr) {
                ss << client->to_string();
            } else {
                ss << " - ";
            }
        }

        ss << "]";

        return ss.str();
    }

private:
    int how_many_chairs;
    std::vector<std::shared_ptr<Client>> chairs;
};

int main() {

    return 0;
}