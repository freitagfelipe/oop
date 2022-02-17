#include <iostream>
#include <person.hpp>

Person::Person(const std::string &name, int age) {
    this->name = name;
    this->age = age;
}

Person::~Person() {}

std::string Person::get_name() const {
    return this->name;
}

void Person::set_name(const std::string &new_name) {
    this->name = new_name;
}

int Person::get_age() const {
    return this->age;
}

void Person::set_age(int new_age) {
    this->age = new_age;
}

std::ostream& operator<<(std::ostream &os, const Person &person) {
    os << "Name: " << person.name << "\nAge: " << person.age;

    return os;
}