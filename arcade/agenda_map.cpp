#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>

class Phone {
public:
    enum Label {casa, oi, tim, vivo, claro};

    Phone(Phone::Label id, std::string number) {
        this->id = id;

        if (Phone::validade(number)) {
            this->number = number;
        }
    }

    void set_id(Phone::Label id) {
        this->id = id;
    }

    std::string get_id() const {
        return Phone::get_label_name(this->id);
    }

    void set_number(std::string number) {
        try {
            Phone::validade(number);
            this->number = number;
        } catch (const std::invalid_argument &e) {
            std::cout << e.what() << std::endl;
        }
    }

    std::string get_number() const {
        return this->number;
    }

    bool operator==(const Phone &phone) {
        return this->id == phone.id && this->number == phone.number;
    }

    static bool validade(const std::string number) {
        for (const char &c : number) {
            if (!(c >= '0' && c <= '9') && c != '(' && c != ')' && c != '.') {
                throw std::invalid_argument("Número inválido.");
            }
        }

        return true;
    }

    friend std::ostream& operator<<(std::ostream &os, const Phone &phone) {
        os << Phone::get_label_name(phone.id) << ":" << phone.number;

        return os;
    }

private:
    Phone::Label id;
    std::string number;

    static std::string get_label_name(Phone::Label id) {
        std::vector<std::string> ids {"casa", "oi", "tim", "vivo", "claro"};

        return ids.at(id);
    }
};

class Contact {
public:
    Contact(std::string name = "") {
        this->name = name;
    }

    void add_phone(Phone::Label id, std::string number) {
        try {
            Phone phone(id, number);
            
            this->add_phone(phone);
        } catch (const std::invalid_argument &e) {
            std::cout << e.what() << std::endl;
        }
    }

    void add_phone(Phone phone) {
        if (std::find(this->phones.begin(), this->phones.end(), phone) == this->phones.end()) {
            this->phones.push_back(phone);
        }
    }

    void remove_phone(int index) {
        if (index < 0 || index >= int(this->phones.size())) {
            std::cout << "Index inválido." << std::endl;

            return;
        }

        this->phones.erase(phones.begin() + index);
    }

    std::vector<Phone> get_phones() const {
        return this->phones;
    }

    std::string get_name() const {
        return this->name;
    }

    void set_name(std::string name) {
        if (name.size() == 0) {
            std::cout << "O nome precisa ter pelo menos uma letra." << std::endl;
            
            return;
        }

        this->name = name;
    }

    bool operator==(const Contact &contact) {
        return this->name == contact.name;
    }

    friend std::ostream& operator<<(std::ostream &os, const Contact &contact) {
        os << "Name: " << contact.name;

        if (contact.phones.size() > 0) {
            os << " | Numbers:";
        }

        for (int i {0}; i < int(contact.phones.size()); ++i) {
            os << " [" << i << ":" << contact.phones.at(i) << "]";
        }

        return os;
    }

private:
    std::string name;
    std::vector<Phone> phones;
};

class Phonebook {
public:
    void add_contact(Contact contact) {
        if (contact.get_name() == "") {
            std::cout << "Adicione um nome ao contato para adicionar na agenda." << std::endl;

            return;
        }

        std::map<std::string, Contact>::iterator it {this->contacts.find(contact.get_name())};

        if (it == this->contacts.end()) {
            this->contacts[contact.get_name()] = contact;

            return;
        }

        for (const Phone &phone : contact.get_phones()) {
            it->second.add_phone(phone);
        }
    }

    void remove_contact(std::string name) {
        this->contacts.erase(name);
    }

    void remove_contact(std::string name, int index) {
        std::map<std::string, Contact>::iterator it {this->contacts.find(name)};

        if (it != this->contacts.end()) {
            it->second.remove_phone(index);
        }
    }

    std::vector<Contact> search(std::string pattern) {
        std::vector<Contact> matches;

        for (const std::pair<const std::string, Contact> &pair : this->contacts) {
            if (pair.second.get_name().find(pattern) != std::string::npos) {
                matches.push_back(pair.second);
            }

            for (const Phone &phone : pair.second.get_phones()) {
                if (phone.get_number().find(pattern) != std::string::npos) {
                    matches.push_back(pair.second);
                }
            }
        }

        return matches;
    }

    Contact get_contact(std::string name) {
        std::map<std::string, Contact>::iterator it {this->contacts.find(name)};

        return it != this->contacts.end() ? it->second : Contact();
    }

    std::map<std::string, Contact> get_contacts() const {
        return this->contacts;
    }

    friend std::ostream& operator<<(std::ostream &os, const Phonebook &phonebook) {
        int count {0};

        for (const std::pair<const std::string, Contact> &pair : phonebook.contacts) {
            if (count++ > 0) {
                os << "\n";
            }

            os << pair.second;
        }

        return os;
    }

private:
    std::map<std::string, Contact> contacts;
};

int main() {

    return 0;
}