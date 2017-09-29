include_directories(include)

add_library(deziras-c++ ${STD_SOURCES} src/iostream.cpp include/cmath ../main.cpp include/cstddef include/cfloat include/cstdint include/cinttypes include/limits include/climits include/type_traits include/initializer_list include/cstdlib include/new src/new.cpp include/typeinfo include/exception src/exception.cpp include/cstdio)
target_link_libraries(deziras-c++ c m)