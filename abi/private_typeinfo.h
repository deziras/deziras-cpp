#pragma once

namespace __cxxabiv1 {
    class __shim_type_info : public std::type_info {
    protected:
        explicit __shim_type_info(char const *name) : std::type_info(name) {}

    public:
        virtual ~__shim_type_info();

        virtual void noop1() const;

        virtual void noop2() const;

        virtual bool can_catch(__shim_type_info const *thrown_type, void *&adjustedPtr) const = 0;
    };

    class __fundamental_type_info : public __shim_type_info {
    protected:
        explicit __fundamental_type_info(char const *name) : __shim_type_info(name) {}

    public:
        virtual~__fundamental_type_info();

        virtual bool can_catch(__shim_type_info const *, void *&) const override;
    };

    class __array_type_info : public __shim_type_info {
    protected:
        explicit __array_type_info(char const *name) : __shim_type_info(name) {}

    public:
        virtual~__array_type_info();

        virtual bool can_catch(__shim_type_info const *, void *&) const override;
    };

    class __enum_type_info : public __shim_type_info {
    protected:
        explicit __enum_type_info(char const *name) : __shim_type_info(name) {}

    public:
        virtual~__enum_type_info();

        virtual bool can_catch(__shim_type_info const *, void *&) const override;
    };

    class __class_type_info;

    struct __dynamic_cast_info {
// const data supplied to the search:

        __class_type_info const *dst_type;
        void const *static_ptr;
        __class_type_info const *static_type;
        std::ptrdiff_t src2dst_offset;

// Data that represents the answer:

        //! pointer to a dst_type which has (static_ptr, static_type) above it
        void const *dst_ptr_leading_to_static_ptr;
        //! pointer to a dst_type which does not have (static_ptr, static_type) above it
        void const *dst_ptr_not_leading_to_static_ptr;

        //! The following three paths are either unknown, public_path or not_public_path.
        //! access of path from dst_ptr_leading_to_static_ptr to (static_ptr, static_type)
        int path_dst_ptr_to_static_ptr;
        //! access of path from (dynamic_ptr, dynamic_type) to (static_ptr, static_type)
        //!    when there is no dst_type along the path
        int path_dynamic_ptr_to_static_ptr;
        //! access of path from (dynamic_ptr, dynamic_type) to dst_type
        //!    (not used if there is a (static_ptr, static_type) above a dst_type).
        int path_dynamic_ptr_to_dst_ptr;

        //! Number of dst_types below (static_ptr, static_type)
        int number_to_static_ptr;
        //! Number of dst_types not below (static_ptr, static_type)
        int number_to_dst_ptr;

// Data that helps stop the search before the entire tree is searched:

        //! is_dst_type_derived_from_static_type is either unknown, yes or no.
        int is_dst_type_derived_from_static_type;
        //! Number of dst_type in tree.  If 0, then that means unknown.
        int number_of_dst_type;
        //! communicates to a dst_type node that (static_ptr, static_type) was found
        //!    above it.
        bool found_our_static_ptr;
        //! communicates to a dst_type node that a static_type was found
        //!    above it, but it wasn't (static_ptr, static_type)
        bool found_any_static_type;
        //! Set whenever a search can be stopped
        bool search_done;
    };

    class __class_type_info : public __shim_type_info {
    protected:
        explicit __class_type_info(char const *name) : __shim_type_info(name) {}

    public:
        virtual~__class_type_info();
    };

    class __si_class_type_info : public __class_type_info {
    protected:
        explicit __si_class_type_info(char const *name) : __class_type_info(name) {}

    public:
        __class_type_info const *__base_type;

        virtual ~__si_class_type_info();
    };

    struct __base_class_type_info {
    public:
        __class_type_info const *__base_type;
        long __offset_flags;

        enum __offset_flags_masks {
            __virtual_mask = 0x1,
            __public_mask = 0x2,
            __offset_shift = 8
        };

    };

    class __vmi_class_type_info : public __class_type_info {
    protected:
        explicit __vmi_class_type_info(char const *name) : __class_type_info(name) {}

    public:
        unsigned int __flags;
        unsigned int __base_count;
        __base_class_type_info __base_info[1];

        virtual ~__vmi_class_type_info();

        enum __flags_masks {
            __non_diamond_repeat_mask = 0x1,
            __diamond_shaped_mask = 0x2
        };
    };


    class __pbase_type_info : public __shim_type_info {
    protected:
        explicit __pbase_type_info(char const *name) : __shim_type_info(name) {}

    public:
        unsigned int __flags;
        std::type_info const *__pointee;

        virtual ~__pbase_type_info();

        enum __masks {
            __const_mask = 0x1,
            __volatile_mask = 0x2,
            __restrict_mask = 0x4,
            __incomplete_mask = 0x8,
            __incomplete_class_mask = 0x10,
            __transaction_safe_mask = 0x20,
            __noexcept_mask = 0x40
        };
    };

    class __pointer_type_info : public __pbase_type_info {
    protected:
        explicit __pointer_type_info(char const *name) : __pbase_type_info(name) {}

    public:
        virtual ~__pointer_type_info();
    };

    class __pointer_to_member_type_info : public __pbase_type_info {
    protected:
        explicit __pointer_to_member_type_info(char const *name) : __pbase_type_info(name) {}

    public:
        __class_type_info const *__context;

        virtual ~__pointer_to_member_type_info();
    };

    extern "C"
    void *__dynamic_cast(void const *sub,
                         __class_type_info const *src,
                         __class_type_info const *dst,
                         std::ptrdiff_t src2dst_offset);
}

