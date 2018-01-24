#include <exception>
#include <cstdio>

namespace std {

    exception_ptr::~exception_ptr() noexcept {
        fprintf(stderr, "exception_ptr not yet implemented\n");
        ::abort();
    }

    exception_ptr::exception_ptr() noexcept : __ptr_(nullptr) {}

    //exception_ptr::exception_ptr(nullptr_t) noexcept : __ptr_(nullptr) {}

    exception_ptr::exception_ptr(exception_ptr const &other) noexcept : __ptr_(other.__ptr_) {
        fprintf(stderr, "exception_ptr not yet implemented\n");
        ::abort();
    }

    exception_ptr &exception_ptr::operator=(exception_ptr const &other) noexcept {
        fprintf(stderr, "exception_ptr not yet implemented\n");
        ::abort();
    }

    exception_ptr current_exception() noexcept {
        fprintf(stderr, "exception_ptr not yet implemented\n");
        ::abort();
    }

    [[noreturn]]
    void rethrow_exception(exception_ptr p) {
        fprintf(stderr, "exception_ptr not yet implemented\n");
        ::abort();
    }

    nested_exception::nested_exception() noexcept : __ptr_(current_exception()) {}

    nested_exception::~nested_exception() noexcept {}

    [[noreturn]]
    void nested_exception::rethrow_nested() const {
        fprintf(stderr, "exception_ptr not yet implemented\n");
        ::abort();
    }

}