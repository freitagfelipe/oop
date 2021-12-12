#pragma once

#include <person.hpp>
#include <sstream>

class Worker : public Person {
public:
    Worker(std::string name, int age, std::string company, double salary) : Person(name, age) {
        this->company = company;
        this->salary = salary;
    }

    virtual void work() const {
        std::cout << "I'm working..." << std::endl;
    }

    std::string get_company() const {
        return this->company;
    }

    void set_company(std::string new_company) {
        this->company = new_company;
    }

    double get_salary() const {
        return this->salary;
    }

    void set_salary(double salary) {
        this->salary = salary;
    }

    friend std::ostream& operator<<(std::ostream &os, const Worker &worker) {
        const Person &person = worker;

        os << person << "\nCompany: " << worker.company << "\nSalary: " << worker.salary;

        return os;
    }

private:
    std::string company;
    double salary;
};