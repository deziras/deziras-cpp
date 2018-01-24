//
// Created by Glavo on 17-10-1.
//

#include <typeinfo>

namespace std {
    bool type_info::operator==(type_info const &other) const noexcept {
        return __type_name == other.__type_name;
    }

    bool type_info::operator!=(type_info const &other) const noexcept {
        return !this->operator==(other);
    }

    size_t type_info::hash_code() const noexcept {
        return reinterpret_cast<size_t >(__type_name);
    }

    bool type_info::before(const type_info &__arg) const noexcept {
        return __type_name < __arg.__type_name;
    }

    char const *type_info::name() const noexcept {
        return __type_name;
    }

    type_info::~type_info() = default;
}


namespace __cxxabiv1 {
    __shim_type_info::~__shim_type_info() = default;

    __fundamental_type_info::~__fundamental_type_info() = default;

    __array_type_info::~__array_type_info() = default;

    __enum_type_info::~__enum_type_info() = default;

    __class_type_info::~__class_type_info() = default;

    __si_class_type_info::~__si_class_type_info() = default;

    __vmi_class_type_info::~__vmi_class_type_info() = default;

    __pbase_type_info::~__pbase_type_info() = default;

    __pointer_type_info::~__pointer_type_info() = default;

    __pointer_to_member_type_info::~__pointer_to_member_type_info() = default;
}
