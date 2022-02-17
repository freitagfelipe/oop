#pragma once

#include <iostream>
#include <worker.hpp>

class Developer : public Worker {
public:
    Developer(const std::string &name, int age, const std::string &company, double salary, const std::string &favorite_language, const std::string &work_language);

    virtual ~Developer();

    void work() const override;

    std::string get_favorite_language() const;

    void set_favorite_language(const std::string &new_favorite_language);

    std::string get_work_language() const;

    void set_work_language(const std::string &new_work_language);

    friend std::ostream& operator<<(std::ostream &os, const Developer &developer);

private:
    std::string favorite_language;
    std::string work_language;
};