#pragma once

#include <worker.hpp>

class Developer : public Worker {
public:
    Developer(std::string name, int age, std::string company, double salary, std::string favorite_language, std::string work_language) : Worker(name, age, company, salary) {
        this->favorite_language = favorite_language;
        this->work_language = work_language;
    }

    void work() const override {
        std::cout << "I'm working with my " << this->work_language << std::endl;
    }

    std::string get_favorite_language() const {
        return this->favorite_language;
    }

    void set_favorite_language(std::string new_favorite_language) {
        this->favorite_language = new_favorite_language;
    }

    std::string get_work_language() const {
        return this->work_language;
    }

    void set_work_language(std::string new_work_language) {
        this->work_language = new_work_language;
    }

    friend std::ostream& operator<<(std::ostream &os, const Developer &developer) {
        const Worker &worker = developer;

        os << worker << "\nFavorite language: " << developer.favorite_language << "\nWork language: " << developer.work_language;

        return os;
    }

private:
    std::string favorite_language;
    std::string work_language;
};