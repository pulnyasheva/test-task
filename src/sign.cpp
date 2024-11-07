#include "sign.h"

void create_throw(const char* fmt, ...) {
    char buffer[256];

    va_list args;
    va_start(args, fmt);
    std::vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);

    throw std::invalid_argument(buffer);
}

void SignDatabase::add_sign(const Sign& sign) {
    if (signs.find(sign.id) != signs.end()) {
        create_throw("Sign with ID %u already exists.", sign.id);
    }
    signs[sign.id] = sign;
}

void SignDatabase::remove_sign(const unsigned int id) {
    if (signs.find(id) == signs.end()) {
        WARN("Sign with ID %u not found.", id);
        return;
    }
    signs.erase(id);
}
std::optional<Sign> SignDatabase::find_sign(const unsigned int id) {
    const auto it = signs.find(id);
    if (it == signs.end()) {
        WARN("Sign with ID %u not found.", id);
        return std::nullopt;
    }
    return it->second;
}

void SignDatabase::add_signs(const std::vector<Sign>& new_signs) {
    for (const auto& sign : new_signs) {
        add_sign(sign);
    }
}
