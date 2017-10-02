#pragma once

#include <typeinfo>

namespace __cxxabiv1 {

    class __shim_type_info : public std::type_info {
    public:
        virtual ~__shim_type_info();

        virtual void noop1() const;

        virtual void noop2() const;

        virtual bool can_catch(__shim_type_info const *thrown_type,
                               void *&adjustedPtr) const = 0;
    };

    class __fundamental_type_info : public __shim_type_info {
    public:
        ~__fundamental_type_info() override;

        bool can_catch(__shim_type_info const *,
                       void *&) const override;
    };

    class __array_type_info : public __shim_type_info {
    public:
        virtual ~__array_type_info();

        bool can_catch(__shim_type_info const *,
                       void *&) const override;
    };

    class __function_type_info : public __shim_type_info {
    public:
        virtual ~__function_type_info();

        bool can_catch(__shim_type_info const *,
                       void *&) const override;
    };

    class __enum_type_info : public __shim_type_info {
    public:
        virtual ~__enum_type_info();

        bool can_catch(__shim_type_info const *,
                       void *&) const override;
    };

    enum {
        unknown = 0,
        public_path,
        not_public_path,
        yes,
        no
    };

    class __class_type_info;

    struct __dynamic_cast_info {
        __class_type_info const *dst_type;
        void const *static_ptr;
        __class_type_info const *static_type;
        std::ptrdiff_t src2dst_offset;


        void const *dst_ptr_leading_to_static_ptr;
        void const *dst_ptr_not_leading_to_static_ptr;

        int path_dst_ptr_to_static_ptr;
        int path_dynamic_ptr_to_static_ptr;
        int path_dynamic_ptr_to_dst_ptr;

        int number_to_static_ptr;
        int number_to_dst_ptr;


        int is_dst_type_derived_from_static_type;
        int number_of_dst_type;
        bool found_our_static_ptr;
        bool found_any_static_type;
        bool search_done;
    };

// Has no base class
    class __class_type_info : public __shim_type_info {
    public:
        ~__class_type_info() override;

        void process_static_type_above_dst(__dynamic_cast_info *,
                                           void const *,
                                           void const *, int) const;

        void process_static_type_below_dst(__dynamic_cast_info *,
                                           void const *, int) const;

        void process_found_base_class(__dynamic_cast_info *, void *,
                                      int) const;

        virtual void search_above_dst(__dynamic_cast_info *,
                                      void const *, void const *,
                                      int, bool) const;

        virtual void
        search_below_dst(__dynamic_cast_info *, void const *, int, bool) const;

        virtual bool can_catch(__shim_type_info const *,
                               void *&) const;

        virtual void
        has_unambiguous_public_base(__dynamic_cast_info *, void *, int) const;
    };

// Has one non-virtual public base class at offset zero
    class __si_class_type_info : public __class_type_info {
    public:
        const __class_type_info *__base_type;

        virtual ~__si_class_type_info();

        virtual void search_above_dst(__dynamic_cast_info *,
                                      void const *, void const *,
                                      int, bool) const;

        virtual void
        search_below_dst(__dynamic_cast_info *, void const *, int, bool) const;

        virtual void
        has_unambiguous_public_base(__dynamic_cast_info *, void *, int) const;
    };

    struct __base_class_type_info {
    public:
        const __class_type_info *__base_type;
        long __offset_flags;

        enum __offset_flags_masks {
            __virtual_mask = 0x1,
            __public_mask = 0x2, // base is public
            __offset_shift = 8
        };

        void search_above_dst(__dynamic_cast_info *, void const *, void const *, int, bool) const;

        void search_below_dst(__dynamic_cast_info *, void const *, int, bool) const;

        void has_unambiguous_public_base(__dynamic_cast_info *, void *, int) const;
    };

// Has one or more base classes
    class __vmi_class_type_info : public __class_type_info {
    public:
        unsigned int __flags;
        unsigned int __base_count;
        __base_class_type_info __base_info[1];

        enum __flags_masks {
            __non_diamond_repeat_mask = 0x1, // has two or more distinct base class
            //    objects of the same type
                    __diamond_shaped_mask = 0x2      // has base class object with two or
            //    more derived objects
        };

        virtual ~__vmi_class_type_info();

        virtual void search_above_dst(__dynamic_cast_info *,
                                      void const *, void const *,
                                      int, bool) const;

        virtual void
        search_below_dst(__dynamic_cast_info *, void const *, int, bool) const;

        virtual void
        has_unambiguous_public_base(__dynamic_cast_info *, void *, int) const;
    };

    class __pbase_type_info : public __shim_type_info {
    public:
        unsigned int __flags;
        const __shim_type_info *__pointee;

        enum __masks {
            __const_mask = 0x1,
            __volatile_mask = 0x2,
            __restrict_mask = 0x4,
            __incomplete_mask = 0x8,
            __incomplete_class_mask = 0x10,
            __transaction_safe_mask = 0x20,
            // This implements the following proposal from cxx-abi-dev (not yet part of
            // the ABI document):
            //
            //   http://sourcerytools.com/pipermail/cxx-abi-dev/2016-October/002986.html
            //
            // This is necessary for support of http://wg21.link/p0012, which permits
            // throwing noexcept function and member function pointers and catching
            // them as non-noexcept pointers.
                    __noexcept_mask = 0x40,

            // Flags that cannot be removed by a standard conversion.
                    __no_remove_flags_mask = __const_mask | __volatile_mask | __restrict_mask,
            // Flags that cannot be added by a standard conversion.
                    __no_add_flags_mask = __transaction_safe_mask | __noexcept_mask
        };

        virtual ~__pbase_type_info();

        virtual bool can_catch(const __shim_type_info *,
                               void *&) const;
    };

    class __pointer_type_info : public __pbase_type_info {
    public:
        virtual ~__pointer_type_info();

        virtual bool can_catch(const __shim_type_info *,
                               void *&) const;

        bool can_catch_nested(const __shim_type_info *) const;
    };

    class __pointer_to_member_type_info
            : public __pbase_type_info {
    public:
        const __class_type_info *__context;

        virtual ~__pointer_to_member_type_info();

        virtual bool can_catch(const __shim_type_info *,
                               void *&) const;

        bool can_catch_nested(const __shim_type_info *) const;
    };

}  // __cxxabiv1