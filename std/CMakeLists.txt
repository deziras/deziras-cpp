include_directories(include)
include_directories(abi/include)

add_library(deziras-c++
        src/iostream.cpp
        include/cmath
        include/cstddef
        include/cfloat
        include/cstdint
        include/cinttypes
        include/limits
        include/climits
        include/type_traits
        include/initializer_list
        include/cstdlib
        include/new
        src/new.cpp
        include/typeinfo
        include/exception
        src/exception.cpp
        include/cstdio
        src/typeinfo.cpp
        include/cstring
        include/unwind.h
        include/iostream src/exception_ptr.cpp include/csetjmp include/ctime include/cerrno include/cassert include/csignal include/cstdarg include/system_error include/stdexcept include/string include/ostream src/string.cpp include/memory include/utility)
target_link_libraries(deziras-c++)