//
// Created by Glavo on 17-9-29.
//

#include <new>

using namespace std;

static std::new_handler newHandler = nullptr;

namespace std {
    const nothrow_t nothrow = nothrow_t{};

    const char *bad_alloc::what() const noexcept {
        return "std::bad_alloc";
    }

    char const* bad_array_new_length::what() const noexcept {
        return "std::bad_array_new_length";
    }

    std::new_handler get_new_handler() noexcept {
        return newHandler;
    }

    std::new_handler set_new_handler(std::new_handler new_p) {
        newHandler = new_p;
    }
}


void *operator new(std::size_t size) {
    if (size == 0)
        size = 1;
    void *p;
    while ((p = ::malloc(size)) == nullptr) {
        std::new_handler nh = std::get_new_handler();
        if (nh)
            nh();
        else {
            throw std::bad_alloc();
        }
    }
    return p;
}


void *operator new(size_t size, std::nothrow_t const &) noexcept {
    void *p = nullptr;
    try {
        p = ::operator new(size);
    } catch (...) {}
    return p;
}


void *operator new[](size_t size) {
    return ::operator new(size);
}

void *operator new[](size_t size, std::nothrow_t const &) noexcept {
    void *p = nullptr;

    try {
        p = ::operator new[](size);
    }
    catch (...) {}

    return p;
}


void operator delete(void *ptr) {
    if (ptr)
        ::free(ptr);
}

void operator delete(void *ptr, std::nothrow_t const &) noexcept {
    ::operator delete(ptr);
}

void operator delete(void *ptr, size_t) noexcept {
    ::operator delete(ptr);
}

void operator delete[](void *ptr) {
    ::operator delete(ptr);
}

void operator delete[](void *ptr, std::nothrow_t const &) noexcept {
    ::operator delete[](ptr);
}

void operator delete[](void *ptr, size_t) noexcept {
    ::operator delete[](ptr);
}


void *operator new(std::size_t size, std::align_val_t alignment) {
    if (size == 0)
        size = 1;
    if (static_cast<size_t>(alignment) < sizeof(void *))
        alignment = std::align_val_t(sizeof(void *));
    void *p;
    while (::posix_memalign(&p, static_cast<size_t>(alignment), size) != 0) {
        std::new_handler nh = std::get_new_handler();
        if (nh)
            nh();
        else {
            throw std::bad_alloc();
        }
    }
    return p;
}


void *operator new(size_t size, std::align_val_t alignment, std::nothrow_t const &) noexcept {
    void *p = nullptr;
    try {
        p = ::operator new(size, alignment);
    }
    catch (...) {
    }
    return p;
}


void *operator new[](size_t size, std::align_val_t alignment) {
    return ::operator new(size, alignment);
}


void *operator new[](size_t size, std::align_val_t alignment, std::nothrow_t const &) noexcept {
    void *p = nullptr;
    try {
        p = ::operator new[](size, alignment);
    }
    catch (...) {
    }
    return p;
}


void operator delete(void *ptr, std::align_val_t) noexcept {
    if (ptr)::free(ptr);
}


void operator delete(void *ptr, std::align_val_t alignment, std::nothrow_t const &) noexcept {
    ::operator delete(ptr, alignment);
}


void operator delete(void *ptr, size_t, std::align_val_t alignment) noexcept {
    ::operator delete(ptr, alignment);
}


void operator delete[](void *ptr, std::align_val_t alignment) noexcept {
    ::operator delete(ptr, alignment);
}


void operator delete[](void *ptr, std::align_val_t alignment, std::nothrow_t const &) noexcept {
    ::operator delete[](ptr, alignment);
}


void operator delete[](void *ptr, size_t, std::align_val_t alignment) noexcept {
    ::operator delete[](ptr, alignment);
}
