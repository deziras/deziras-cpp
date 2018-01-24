#include "cxxabi.h"
#include <cstdlib>

const size_t bufferSize = 256;

static uint8_t exceptionBuffer[bufferSize];
static bool hasAllocateBuffer = false;

namespace __cxxabiv1 {
    extern "C" {
    void *__cxa_allocate_exception(size_t thrown_size) {
        void *ans = nullptr;
        if ((thrown_size > bufferSize) || hasAllocateBuffer) {
            ans = ::malloc(thrown_size);
            if (ans == nullptr) {
                std::terminate();
            }
        } else {
            hasAllocateBuffer = true;
            ans = &exceptionBuffer[0];
        }
        return ans;
    }

    void __cxa_free_exception(void *thrown_exception) {
        if (thrown_exception == &exceptionBuffer[0]) {
            hasAllocateBuffer = false;
        } else {
            ::free(thrown_exception);
        }
    }
    }

    [[noreturn]]
    void __cxa_throw(void *thrown_exception, std::type_info *tinfo, void (*dest)(void *)) {
        std::terminate();//todo
    }
}