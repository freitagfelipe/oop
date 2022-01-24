#pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include <functional>

namespace aux {
    std::vector<std::string> split(std::istream &is, char delimiter) {
        std::vector<std::string> result;
        std::string token;

        while (std::getline(is, token, delimiter)) {
            if (token.size() > 0) {
                result.push_back(token);
            }
        }

        return result;
    }


    std::vector<std::string> split(const std::string &line, char delimiter) {
        std::istringstream iss(line);

        return aux::split(iss, delimiter);
    }

    std::vector<std::string> get_cmd() {
        std::string line;

        std::getline(std::cin, line);

        return aux::split(line, ' ');
    }

    template <typename T>
    std::vector<T> slice(const std::vector<T> &v, int start, int end = 0) {
        std::vector<T> result;

        if (end == 0) {
            end = v.size();
        } else if (end < 0) {
            end = v.size() + end;
        }

        if (start < 0) {
            start = v.size() + start;
        }

        if (start >= end) {
            return result;
        }

        auto it_start {v.begin()};
        auto it_end {v.begin()};

        std::advance(it_start, start);
        std::advance(it_end, end);

        std::copy(it_start, it_end, std::back_inserter(result));

        return result;
    }

    std::string join(const auto &container, const std::string delimiter, auto fn) {
        if (container.size() == 0) {
            return "";
        }

        std::ostringstream oss;

        int count {0};

        for (const auto &item : container) {
            if (count++ > 0) {
                oss << delimiter;
            }
            
            oss << fn(item);
        }

        return oss.str();
    }

    std::string join(const auto &container, const std::string &delimiter) {
        return join(container, delimiter, [](auto &x) { return x; });
    }
}