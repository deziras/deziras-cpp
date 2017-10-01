//
// Created by Glavo on 17-9-30.
//

#include <exception>
#include <cstdio>
#include <cstdlib>

#ifdef __GNUC__

#include "linux/exception.h"

#endif

#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnusedImportStatement"
#pragma ide diagnostic ignored "ClangTidyInspection"

namespace std {
    static int nexception;
    static void *exception_stack;

    static void default_unexpected_handle() {
        fprintf(stderr, "terminating");
        exit(6);
    }

    static unexpected_handler uh = default_unexpected_handle;

    static terminate_handler th = default_unexpected_handle;

    unexpected_handler get_unexpected() noexcept {
        return uh;
    }

    unexpected_handler set_unexpected(unexpected_handler f) noexcept {
        auto old = uh;
        uh = f;
        return old;
    }

    [[noreturn]] void unexpected() {
        try {
            uh();
            // handler should not return
            fprintf(stderr,
                    "terminate_handler unexpectedly returned\n");
            ::abort();
        }
        catch (...) {
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
        }
        catch (...) {
            fprintf(stderr,
                    "terminate_handler unexpectedly threw an exception\n");
            ::abort();
        }
    }

    int uncaught_exceptions() noexcept {
        return nexception;
    }

    bool std::uncaught_exception() noexcept {
        return std::uncaught_exceptions() > 0;
    }
}


#pragma clang diagnostic pop