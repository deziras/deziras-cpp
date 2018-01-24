cmake_minimum_required(VERSION 3.8)
project(deziras)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -nodefaultlibs -nostdinc++")

add_subdirectory(std)

include_directories(std/include)

add_executable(main main.cpp)
target_link_libraries(main deziras-c++)
