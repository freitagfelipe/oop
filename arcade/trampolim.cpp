#include <iostream>
#include <sstream>
#include <memory>
#include <vector>
#include <list>
#include <map>

class Kid {
public:
    Kid(std::string name, int age) {
        this->name = name;
        this->age = age;
    }

    std::string to_string() const {
        std::stringstream ss;

        ss << this->name << ":" << this->age;

        return ss.str();
    }

    void set_age(int age) {
        this->age = age;
    }

    int get_age() const {
        return this->age;
    }

    void set_name(std::string name) {
        this->name = name;
    }

    std::string get_name() const {
        return this->name;
    }

private:
    int age;
    std::string name;
};

class Trampoline {
public:
    Trampoline (double cost_to_pay = 5, int max_players = 4) {
        this->cost_to_pay = cost_to_pay;
        this->max_players = max_players;
        this->cash_register = 0;
        this->is_closed = false;
    }

    void arrive(const std::shared_ptr<Kid> &kid) {
        this->waiting.push_back(kid);
        this->balance[kid->get_name()] = 0;
    }

    void in() {
        if (this->is_closed) {
            std::cout << "O trampolim está fechado!" << std::endl;

            return;
        }

        if (int(this->playing.size()) >= this->max_players) {
            std::cout << "O trampolim está cheio!" << std::endl;

            return;
        }

        if (this->waiting.size() == 0) {
            std::cout << "A fila está vazia!" << std::endl;

            return;
        }

        this->playing.push_back(this->waiting.front());
        this->balance[this->waiting.front()->get_name()] += this->cost_to_pay;
        this->waiting.pop_front();
    }

    void out() {
        if (this->playing.size() == 0) {
            std::cout << "O trampolim está vazio!" << std::endl;

            return;
        }

        this->waiting.push_back(this->playing.front());
        this->playing.erase(this->playing.begin());
    }

    std::shared_ptr<Kid> remove(std::string kid_name) {
        std::shared_ptr<Kid> kid_shared_ptr = Trampoline::remove(this->playing, kid_name);

        if (kid_shared_ptr == nullptr) {
            kid_shared_ptr = Trampoline::remove(this->waiting, kid_name);
        }

        if (kid_shared_ptr != nullptr) {
            std::map<std::string, double>::iterator it = this->balance.find(kid_name);

            this->cash_register += it->second;

            this->balance.erase(it);
        }

        return kid_shared_ptr;
    }

    void close() {
        if (!this->is_closed) {
            std::cout << "O trampolim fechado!" << std::endl;

            for (const std::pair<const std::string, double> &pair : this->balance) {
                this->cash_register += pair.second;
            }

            this->is_closed = true;
            this->playing.clear();
            this->waiting.clear();
            this->balance.clear();
        }
    }

    void open() {
        if (this->is_closed) {
            std::cout << "O trampolim aberto!" << std::endl;

            this->is_closed = false;
        }
    }

    std::string to_string() const {
        std::stringstream ss;

        ss << "Fila: ";

        int count {0};

        for (const std::shared_ptr<Kid> &kid : this->waiting) {
            if (count++ > 0) {
                ss << " | ";
            }

            ss << kid->to_string(); 
        }

        ss << "\nBrincando: ";

        count = 0;

        for (const std::shared_ptr<Kid> &kid : this->playing) {
            if (count++ > 0) {
                ss << " | ";
            }

            ss << kid->to_string();
        }

        return ss.str();
    }

    int get_cash_register() const {
        return this->cash_register;
    }

private:
    std::vector<std::shared_ptr<Kid>> playing;
    std::list<std::shared_ptr<Kid>> waiting;
    std::map<std::string, double> balance;
    int cash_register;
    int max_players;
    double cost_to_pay;
    bool is_closed;

    static std::shared_ptr<Kid> remove(auto &container, std::string kid_name) {
        for (auto it {container.begin()}; it != container.end(); ++it) {
            if (it->get()->get_name() == kid_name) {
                std::shared_ptr<Kid> kid_shared_ptr = *it;

                container.erase(it);

                return kid_shared_ptr;
            }
        }

        return nullptr;
    }
};

int main() {

    return 0;
}