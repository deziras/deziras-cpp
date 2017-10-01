#pragma once

#include <cstdlib>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "ClangTidyInspection"

extern "C"
void *__cxa_allocate_exception(size_t thrown_size) noexcept {
    return malloc(thrown_size);
}

extern "C"
void __cxa_free_exception(void *thrown_exception) noexcept {
    free(thrown_exception);
}

extern "C"
void __cxa_throw(
        void *thrown_exception,
        struct type_info *tinfo,
        void (*dest)(void *)) {
    printf("throw\n");
    exit(0);
}


#pragma clang diagnostic pop