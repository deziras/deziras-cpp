include_directories(include)

add_library(deziras-c++ ${STD_SOURCES} src/iostream.cpp include/cmath ../main.cpp include/cstddef include/cfloat include/cstdint include/cinttypes include/limits include/climits include/type_traits)
target_link_libraries(deziras-c++ c m)