//
// Created by Glavo on 17-9-30.
//

#include <exception>
#include <cstdio>
#include <cstdlib>

static int __exceptions = 0;


static void default_unexpected_handle() {
    fprintf(stderr, "terminating");
    ::exit(6);
}

static void *exception_stack;
static std::unexpected_handler uh = default_unexpected_handle;
static std::terminate_handler th = default_unexpected_handle;


namespace std {
    exception::exception() noexcept = default;

    exception::exception(exception const &) noexcept = default;

    exception &exception::operator=(exception const &)  noexcept = default;

    exception::~exception() noexcept = default;

    char const *exception::what() const noexcept {
        return "std::exception";
    }

    bad_exception::bad_exception() noexcept = default;

    bad_exception::bad_exception(bad_exception const &) noexcept = default;

    bad_exception &bad_exception::operator=(bad_exception const &) noexcept = default;

    bad_exception::~bad_exception() noexcept = default;

    char const *bad_exception::what() const noexcept {
        return "std::bad_exception";
    }

    unexpected_handler get_unexpected() noexcept {
        return uh;
    }

    unexpected_handler set_unexpected(unexpected_handler f) noexcept {
        auto old = uh;
        uh = f;
        return old;
    }

    [[noreturn]]
    void unexpected() {
        try {
            uh();
            // handler should not return
            fprintf(stderr,
                    "terminate_handler unexpectedly returned\n");
            ::abort();
        } catch (...) {
            fprintf(stderr,
                    "terminate_handler unexpectedly threw an exception\n");
            ::abort();
        }
    }

    terminate_handler get_terminate() noexcept {
        return th;
    }

    terminate_handler set_terminate(terminate_handler f) noexcept {
        auto old = th;
        th = f;
        return th;
    }

    void terminate() noexcept {
        try {
            th();
            // handler should not return
            fprintf(stderr,
                    "terminate_handler unexpectedly returned\n");
            ::abort();
        } catch (...) {
            fprintf(stderr,
                    "terminate_handler unexpectedly threw an exception\n");
            ::abort();
        }
    }

    int uncaught_exceptions() noexcept {
        return __exceptions;
    }

    bool uncaught_exception() noexcept {
        return std::uncaught_exceptions() > 0;
    }

}

