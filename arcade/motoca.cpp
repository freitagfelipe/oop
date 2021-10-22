#include <iostream>
#include <iomanip>
#include <sstream>

class Pessoa {
private:
    std::string name;
    int age;

public:
    Pessoa(std::string name, int age) : name {name}, age {age} {}

    std::string toString() const {
        std::stringstream ss;

        ss << "Person {\n\tname: " << this->name << ",\n\tage: " << this->age << "\n}"; 

        return ss.str();
    }

    int getAge() const {
        return this->age;
    }

    std::string getName() const {
        return this->name;
    }
};

class Moto {
private:
    Pessoa *person;
    int power;
    int time;
    int distance;

public:
    Moto() {
        this->person = nullptr;
        this->power = 1;
        this->time = 0;
        this->distance = 0;
    }

    Moto(int power) {
        this->person = nullptr;
        this->power = power;
        this->time = 0;
        this->distance = 0;
    }

    void buy(int time) {
        this->time += time;
    }

    void drive(int time) {
        if (this->person == nullptr) {
            return;
        } else if (this->person->getAge() > 10) {
            std::cout << "Você necessita ter menos de 10 anos para andar na moto." << std::endl;

            return;
        } else if (this->time == 0) {
            std::cout << "Você não tem tempo." << std::endl;

            return;
        }

        this->distance += time;

        if (time > this->time) {
            this->time = 0;

            std::cout << "O tempo acabou. Você andou " << this->distance << "." << std::endl;
        } else if (time <= this->time) {
            this->time -= time;
        }
    }

    void honk() {
        if (this->person == nullptr) {
            std::cout << "P" << std::setw(this->power + 1) << std::setfill('e') << "m" << std::endl;
        }
    }

    bool in(Pessoa *person) {
        if (this->person == nullptr) {
            this->person = person;

            std::cout << person->toString() << std::endl;

            return true;
        }

        return false;
    }

    Pessoa* out() {
        if (this->person != nullptr) {
            return std::exchange(this->person, nullptr);
        }

        return nullptr;
    }

    std::string toString() {
        std::stringstream ss;

        if (this->person == nullptr) {
            ss << "Moto {\n\tpower: " << this->power << ",\n\ttime: " << this->time << ",\n\tdistance: " << this->distance << "\n}";
        } else {
            ss << "Moto {\n\t" << "person: {\n\t\tname: " << this->person->getName() << ",\n\t\tage: " << this->person->getAge() << "\n\t},\n\tpower: " << this->power << ",\n\ttime: " << this->time << ",\n\tdistance: " << this->distance << "\n}";
        }

        return ss.str();
    }
};

int main() {

    return 0;
}