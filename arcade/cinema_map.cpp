#include <iostream>
#include <sstream>
#include <memory>
#include <vector>
#include <map>

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
    }

    void cancel(std::string name) {
        for (const std::pair<const int, std::shared_ptr<Client>>& pair : this->chairs) {
            if (pair.second->get_name() == name) {
                this->chairs.erase(pair.first);

                return;
            }
        }

        std::cout << "Cliente não está no cinema!" << std::endl;
    }

    bool reserve(std::string name, std::string phone, int chair_number) {
        if (chair_number < 0 || chair_number >= this->how_many_chairs) {
            std::cout << "Escolha uma cadeira válida!" << std::endl;

            return false;
        } else if (this->chairs.find(chair_number) != this->chairs.end()) {
            std::cout << "Cadeira já reservada!" << std::endl;

            return false;
        }

        for (const std::pair<const int, std::shared_ptr<Client>> &pair : this->chairs) {
            if (pair.second->get_name() == name) {
                std::cout << "Cliente já está no cinema!" << std::endl;

                return false;
            }
        }

        this->chairs[chair_number] = std::make_shared<Client>(name, phone);

        return true;
    }

    std::map<int, std::shared_ptr<Client>>& get_chairs() {
        return this->chairs;
    }

    std::string to_string() const {
        std::vector<std::string> lines(this->how_many_chairs, " - ");
        std::stringstream ss;

        ss << "[";

        for (const std::pair<const int, std::shared_ptr<Client>> &pair : this->chairs) {
            lines.at(pair.first) = pair.second->to_string();
        }

        for (std::string& chair : lines) {
            ss << chair;
        }

        ss << "]";

        return ss.str();
    }

private:
    int how_many_chairs;
    std::map<int, std::shared_ptr<Client>> chairs;
};

int main() {

    return 0;
}