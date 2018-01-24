//
// Created by Glavo on 17-10-1.
//

#include <typeinfo>
#include <cstring>

namespace std {
    type_info::~type_info() = default;

    const char *bad_cast::what() const noexcept {
        return "std::bad_cast";
    }

    const char *bad_typeid::what() const noexcept {
        return "std::bad_typeid";
    }
}


