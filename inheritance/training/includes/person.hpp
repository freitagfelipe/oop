#pragma once

#include <iostream>

class Person {
public:
    Person(const std::string &name, int age);

    virtual ~Person();

    std::string get_name() const;

    void set_name(const std::string &new_name);

    int get_age() const;

    void set_age(int new_age);

    friend std::ostream& operator<<(std::ostream &os, const Person &person);

private:
    std::string name;
    int age;
};