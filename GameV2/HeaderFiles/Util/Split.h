#pragma once
#ifndef UTILITY
#define UTILITY

#include <string>
#include <vector>

inline std::vector<std::string> split(const std::string& input, char delim) {
    std::vector<std::string> result;
    std::string current;

    for (char c : input) {
        if (c == delim) {
            if (!current.empty())
                result.push_back(current);
            current.clear();
        }
        else {
            current.push_back(c);
        }
    }
    if (!current.empty()) result.push_back(current);
    return result;
}

#endif