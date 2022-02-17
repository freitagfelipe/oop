#include <iostream>
#include <person.hpp>
#include <worker.hpp>

Worker::Worker(const std::string &name, int age, const std::string &company, double salary) : Person(name, age) {
    this->company = company;
    this->salary = salary;
}

Worker::~Worker() {}

void Worker::work() const {
    std::cout << "I'm working..." << std::endl;
}

std::string Worker::get_company() const {
    return this->company;
}

void Worker::set_company(const std::string &new_company) {
    this->company = new_company;
}

double Worker::get_salary() const {
    return this->salary;
}

void Worker::set_salary(double new_salary) {
    this->salary = new_salary;
}

std::ostream& operator<<(std::ostream &os, const Worker &worker) {
    const Person &person = worker;

    os << person << "\nCompany: " << worker.company << "\nSalary: " << worker.salary;

    return os;
}