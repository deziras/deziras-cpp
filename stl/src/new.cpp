//
// Created by Glavo on 17-9-29.
//

#include <new>
#include <cstdlib>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "ClangTidyInspection"

using namespace std;

static std::new_handler newHandler = nullptr;

namespace std {
    const nothrow_t nothrow = nothrow_t{};

    std::new_handler get_new_handler() noexcept {
        return newHandler;
    }

    std::new_handler set_new_handler(std::new_handler new_p) {
        newHandler = new_p;
    }
}


void *
operator new(std::size_t size) {
    if (size == 0)
        size = 1;
    void *p;
    while ((
                   p = ::malloc(size)
           ) == nullptr) {
// If malloc fails and there is a new_handler,
// call it to try free up memory.
        std::new_handler nh = std::get_new_handler();
        if (nh)

            nh();

        else
#ifndef _LIBCPP_NO_EXCEPTIONS
            throw

                    std::bad_alloc();

#else
        break;
#endif
    }
    return
            p;
}


void *
operator new(size_t size, std::nothrow_t const &) noexcept {
    void *p = 0;
#ifndef _LIBCPP_NO_EXCEPTIONS
    try {
#endif  // _LIBCPP_NO_EXCEPTIONS
        p = ::operator new(size);
#ifndef _LIBCPP_NO_EXCEPTIONS
    }
    catch (...) {
    }
#endif  // _LIBCPP_NO_EXCEPTIONS
    return p;
}


void *
operator new[](size_t size) {
    return
            ::operator new(size);
}


void *
operator new[](size_t size, std::nothrow_t const &) noexcept {
    void *p = 0;

    try {
        p = ::operator new[](size);
    }
    catch (...) {
    }

    return p;
}


void
operator delete(void *ptr) noexcept {
    if (ptr)
        ::free(ptr);
}

void
operator delete(void *ptr, std::nothrow_t const &) noexcept {
    ::operator delete(ptr);
}

void
operator delete(void *ptr, size_t) noexcept {
    ::operator delete(ptr);
}

void
operator delete[](void *ptr) noexcept {
    ::operator delete(ptr);
}

void
operator delete[](void *ptr, std::nothrow_t const &) noexcept {
    ::operator delete[](ptr);
}

void
operator delete[](void *ptr, size_t) noexcept {
    ::operator delete[](ptr);
}


void *
operator new(std::size_t size, std::align_val_t alignment) {
    if (size == 0)
        size = 1;
    if (static_cast
                <size_t>(alignment)
        < sizeof(void *))
        alignment = std::align_val_t(sizeof(void *));
    void *p;
#if defined(_LIBCPP_MSVCRT_LIKE)
    while ((p = _aligned_malloc(size, static_cast<size_t>(alignment))) == nullptr)
#else
    while (
            ::posix_memalign(&p,
                             static_cast
                                     <size_t>(alignment), size
            ) != 0)
#endif
    {
// If posix_memalign fails and there is a new_handler,
// call it to try free up memory.
        std::new_handler nh = std::get_new_handler();
        if (nh)

            nh();

        else {
#ifndef _LIBCPP_NO_EXCEPTIONS
            throw

                    std::bad_alloc();

#else
            p = nullptr; // posix_memalign doesn't initialize 'p' on failure
                        break;
#endif
        }
    }
    return
            p;
}


void *
operator new(size_t size, std::align_val_t alignment, std::nothrow_t const &) noexcept {
    void *p = 0;
#ifndef _LIBCPP_NO_EXCEPTIONS
    try {
#endif  // _LIBCPP_NO_EXCEPTIONS
        p = ::operator new(size, alignment);
#ifndef _LIBCPP_NO_EXCEPTIONS
    }
    catch (...) {
    }
#endif  // _LIBCPP_NO_EXCEPTIONS
    return p;
}


void *
operator new[](size_t size, std::align_val_t alignment) {
    return ::operator new(size, alignment);
}


void *
operator new[](size_t size, std::align_val_t alignment, std::nothrow_t const &) noexcept {
    void *p = 0;
#ifndef _LIBCPP_NO_EXCEPTIONS
    try {
#endif  // _LIBCPP_NO_EXCEPTIONS
        p = ::operator new[](size, alignment);
#ifndef _LIBCPP_NO_EXCEPTIONS
    }
    catch (...) {
    }
#endif  // _LIBCPP_NO_EXCEPTIONS
    return p;
}


void
operator delete(void *ptr, std::align_val_t) noexcept {
    if (ptr)
#if defined(_LIBCPP_MSVCRT_LIKE)
        ::_aligned_free(ptr);
#else
        ::free(ptr);
#endif
}


void
operator delete(void *ptr, std::align_val_t alignment, std::nothrow_t const &) noexcept {
    ::operator delete(ptr, alignment);
}


void
operator delete(void *ptr, size_t, std::align_val_t alignment) noexcept {
    ::operator delete(ptr, alignment);
}


void
operator delete[](void *ptr, std::align_val_t alignment) noexcept {
    ::operator delete(ptr, alignment);
}


void
operator delete[](void *ptr, std::align_val_t alignment, std::nothrow_t const &) noexcept {
    ::operator delete[](ptr, alignment);
}


void
operator delete[](void *ptr, size_t, std::align_val_t alignment) noexcept {
    ::operator delete[](ptr, alignment);
}

#pragma clang diagnostic pop