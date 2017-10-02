include_directories(include)
include_directories(../stl/include)

add_library(deziras-abi
        include/deziras/private-typeinfo.h
        src/private-typeinfo.cpp
        )