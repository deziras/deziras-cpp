//
// Created by Glavo on 17-9-30.
//

#include <exception>
#include <cstdio>
#include <cstdlib>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "ClangTidyInspection"
using namespace std;

static void default_unexpected_handle() {
    fprintf(stderr, "terminating");
    exit(6);
}

static unexpected_handler uh = default_unexpected_handle;

static terminate_handler th = default_unexpected_handle;

char const *std::exception::what() const noexcept {
    return "std::exception";
}

char const *std::bad_exception::what() const noexcept {
    return "std::bad_exception";
}

unexpected_handler std::get_unexpected() noexcept {
    return uh;
}

unexpected_handler std::set_unexpected(unexpected_handler f) noexcept {
    auto old = uh;
    uh = f;
    return old;
}

[[noreturn]] void std::unexpected() {
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

terminate_handler std::get_terminate() noexcept {
    return th;
}

terminate_handler std::set_terminate(terminate_handler f) noexcept {
    auto old = th;
    th = f;
    return th;
}

void std::terminate() noexcept {
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

int std::uncaught_exceptions() noexcept {
    ::abort();
}

bool std::uncaught_exception() noexcept {
    return std::uncaught_exceptions() > 0;
}



#pragma clang diagnostic pop