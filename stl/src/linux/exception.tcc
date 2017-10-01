//
// Created by Glavo on 17-9-30.
//
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


#pragma clang diagnostic pop