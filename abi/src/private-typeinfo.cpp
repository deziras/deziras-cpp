//
// Created by Glavo on 17-10-2.
//

#include <deziras/private-typeinfo.h>
#include <cstring>

inline bool is_equal(std::type_info const *x, std::type_info const *y, bool use_strcmp) {
#ifndef _WIN32
    if (!use_strcmp)
        return x == y;
    return strcmp(x->name(), y->name()) == 0;
#else
    return (x == y) || (strcmp(x->name(), y->name()) == 0);
#endif
}

namespace __cxxabiv1 {

    __shim_type_info::~__shim_type_info() = default;

    void __shim_type_info::noop1() const {
    }

    void __shim_type_info::noop2() const {

    }

    __fundamental_type_info::~__fundamental_type_info() = default;

    bool __fundamental_type_info::can_catch(__shim_type_info const *, void *&) const {
        return false;
    }

    __array_type_info::~__array_type_info() = default;

    bool __array_type_info::can_catch(__shim_type_info const *, void *&) const  {
        return false;
    }

    __function_type_info::~__function_type_info() = default;

    bool __function_type_info::can_catch(__shim_type_info const *, void *&) const {
        return false;
    }

    __enum_type_info::~__enum_type_info() = default;


    bool __enum_type_info::can_catch(__shim_type_info const *, void *&) const {
        return false;
    }


    __class_type_info::~__class_type_info() = default;
}
