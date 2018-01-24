#pragma once

#include <unwind.h>
#include <exception>

namespace std {
    class type_info;
}

namespace __cxxabiv1 {
    struct __cxa_exception {
        std::type_info *exceptionType;

        void (*exceptionDestructor)(void *);

        std::unexpected_handler unexpectedHandler;
        std::terminate_handler terminateHandler;
        __cxa_exception *nextException;

        int handlerCount;
        int handlerSwitchValue;
        const char *actionRecord;
        const char *languageSpecificData;
        void *catchTemp;
        void *adjustedPtr;

        _Unwind_Exception unwindHeader;
    };

    struct __cxa_eh_globals {
        __cxa_exception *caughtExceptions;
        unsigned int uncaughtExceptions;
    };

    extern "C" {
    void *__cxa_allocate_exception(size_t thrown_size);

    void __cxa_free_exception(void *thrown_exception);

    [[noreturn]]
    void __cxa_throw(void *thrown_exception, std::type_info *tinfo, void (*dest)(void *));

    void *__cxa_get_exception_ptr(void *exceptionObject);

    void *__cxa_begin_catch(void *exceptionObject);

    void __cxa_end_catch();

    void __cxa_bad_cast();

    void __cxa_bad_typeid();
    }
}

namespace abi = __cxxabiv1;