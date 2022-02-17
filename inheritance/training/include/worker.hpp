#pragma once

#include <iostream>
#include <person.hpp>

class Worker : public Person {
public:
    Worker(const std::string &name, int age, const std::string &company, double salary);

    virtual ~Worker();

    virtual void work() const;

    std::string get_company() const;

    void set_company(const std::string &new_company);

    double get_salary() const;

    void set_salary(double salary);

    friend std::ostream& operator<<(std::ostream &os, const Worker &worker);

private:
    std::string company;
    double salary;
};