#ifndef SIGN_H
#define SIGN_H

#include <iostream>
#include <optional>
#include <unordered_map>
#include <string>
#include <cstdarg>
#include <cstdio>
#include <utility>
#include <vector>

#define WARN(fmt, ...) { \
char buffer[256]; \
std::snprintf(buffer, sizeof(buffer), fmt, __VA_ARGS__); \
std::cerr << "WARNING: " << buffer << std::endl; \
}

struct Coordinates {
    double longitude;
    double latitude;
};

class Sign {
public:
    std::string name;
    unsigned int id;
    Coordinates coordinates;

    Sign() {
    }

    Sign(std::string name, const unsigned int id, const Coordinates &coords)
        : name(std::move(name)), id(id), coordinates(coords) {
    }
};

class SignDatabase {
public:
    void add_sign(const Sign &sign);

    void remove_sign(unsigned int id);

    std::optional<Sign> find_sign(unsigned int id);

    void add_signs(const std::vector<Sign> &new_signs);

private:
    std::unordered_map<unsigned int, Sign> signs;
};

#endif
