//
// Created by glavo on 18-1-24.
//

template<bool use_strcmp>
inline bool is_equal(std::type_info const *x, std::type_info const *y);

template<>
inline bool is_equal<true>(std::type_info const *x, std::type_info const *y) {
    return ::strcmp(x->name(), y->name()) == 0;
}

template<>
inline bool is_equal<false>(std::type_info const *x, std::type_info const *y) {
    return x == y;
}

namespace __cxxabiv1 {
    __shim_type_info::~__shim_type_info() = default;

    void __shim_type_info::noop1() const {}

    void __shim_type_info::noop2() const {}

    __fundamental_type_info::~__fundamental_type_info() = default;

    __array_type_info::~__array_type_info() = default;

    __enum_type_info::~__enum_type_info() = default;

    __class_type_info::~__class_type_info() = default;

    __si_class_type_info::~__si_class_type_info() = default;

    __vmi_class_type_info::~__vmi_class_type_info() = default;

    __pbase_type_info::~__pbase_type_info() = default;

    __pointer_type_info::~__pointer_type_info() = default;

    __pointer_to_member_type_info::~__pointer_to_member_type_info() = default;

    bool __fundamental_type_info::can_catch(__shim_type_info const *thrown_type, void *&) const {
        return is_equal<false>(this, thrown_type);
    }


    bool __array_type_info::can_catch(__shim_type_info const *, void *&) const {
        return false;
    }

    bool __enum_type_info::can_catch(__shim_type_info const *thrown_type, void *&) const {
        return is_equal<false>(this, thrown_type);
    }
}
