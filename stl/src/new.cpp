//
// Created by Glavo on 17-9-29.
//

#include <new>
#include <cstdlib>

using namespace std;

extern const nothrow_t nothrow;

char const *bad_alloc::what() const noexcept {
    return "std::bad_alloc";
}

char const *bad_array_new_length::what() const noexcept {
    return "std::bad_array_new_length";
}

void *operator new(size_t size) {
    void *ptr = malloc(size);
    if (ptr == nullptr)
        throw bad_exception{};
    return ptr;
}

void *operator new[](size_t size) {
    void *ptr = malloc(size);
    if (ptr == nullptr)
        throw bad_exception{};
    return ptr;
}

void operator delete(void *p) {
    free(p);
}

void operator delete[](void *p) {
    free(p);
}


void *operator new(size_t size, nothrow_t &) noexcept {
    return malloc(size);
}

void *operator new[](size_t size, nothrow_t &) noexcept {
    return malloc(size);
}

void operator delete(void *p, nothrow_t &) noexcept {
    free(p);
}

void operator delete[](void *p, nothrow_t &) noexcept {
    free(p);
}
