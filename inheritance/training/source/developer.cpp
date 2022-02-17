#include <iostream>
#include <worker.hpp>
#include <developer.hpp>

Developer::Developer(const std::string &name, int age, const std::string &company, double salary, const std::string &favorite_language, const std::string &work_language) : Worker(name, age, company, salary) {
    this->favorite_language = favorite_language;
    this->work_language = work_language;
}

Developer::~Developer() {}

void Developer::work() const {
    std::cout << "I'm working with my " << this->work_language << std::endl;
}

std::string Developer::get_favorite_language() const {
    return this->favorite_language;
}

void Developer::set_favorite_language(const std::string &new_favorite_language) {
    this->favorite_language = new_favorite_language;
}

std::string Developer::get_work_language() const {
    return this->work_language;
}

void Developer::set_work_language(const std::string &new_work_language) {
    this->work_language = new_work_language;
}

std::ostream& operator<<(std::ostream &os, const Developer &developer) {
    const Worker &worker = developer;

    os << worker << "\nFavorite language: " << developer.favorite_language << "\nWork language: " << developer.work_language;

    return os;
}