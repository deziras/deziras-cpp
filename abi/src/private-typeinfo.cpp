//
// Created by Glavo on 17-10-2.
//

#include <deziras/private-typeinfo.h>
#include <string.h>

static inline bool is_equal(const std::type_info *x, const std::type_info *y, bool use_strcmp) {
#ifndef _WIN32
    if (!use_strcmp)
        return x == y;
    return strcmp(x->name(), y->name()) == 0;
#else
    return (x == y) || (strcmp(x->name(), y->name()) == 0);
#endif
}

namespace __cxxabiv1 {

    __shim_type_info::~__shim_type_info() {

    }

    void __shim_type_info::noop1() const {
    }

    void __shim_type_info::noop2() const {

    }
}
