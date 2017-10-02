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
        src/linux/exception.h
        include/cstdio
        src/typeinfo.cpp
        include/cstring
        abi/include/deziras/private-typeinfo.h
        abi/src/private-typeinfo.cpp
        )
target_link_libraries(deziras-c++ c)