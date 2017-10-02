//
// Created by Glavo on 17-10-1.
//

#include <typeinfo>

namespace std {
    bool type_info::operator==(type_info const &other) const noexcept {
        return type_name == other.type_name;
    }

    bool type_info::operator!=(type_info const &other) const noexcept {
        return !this->operator==(other);
    }

    size_t type_info::hash_code() const noexcept {
        return reinterpret_cast<size_t >(type_name);
    }

    bool type_info::before(const type_info &__arg) const noexcept {
        return type_name < __arg.type_name;
    }

    char const *type_info::name() const noexcept {
        return type_name;
    }
}
