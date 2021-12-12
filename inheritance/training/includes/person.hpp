#pragma once

#include <iostream>

class Person {
public:
    Person(std::string name, int age) {
        this->name = name;
        this->age = age;
    }

    std::string get_name() const {
        return this->name;
    }

    void set_name(std::string name) {
        this->name = name;
    }

    int get_age() const {
        return this->age;
    }

    friend std::ostream& operator<<(std::ostream &os, const Person &person) {
        os << "Name: " << person.name << "\nAge: " << person.age;

        return os;
    }

private:
    std::string name;
    int age;
};