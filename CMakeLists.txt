cmake_minimum_required(VERSION 3.28)
project(
    Assembler
    VERSION 1.0
    DESCRIPTION "A limit order book system written in C++"
    LANGUAGES CXX
)

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

# Library that includes everything except for the main() function.
add_library(assembler_lib)
target_sources(assembler_lib PRIVATE src/order_book.cpp)
target_include_directories(assembler_lib PUBLIC include)

# Executable linked against the library
add_executable(Assembler src/main.cpp)
target_link_libraries(Assembler PUBLIC assembler_lib)

include(CTest)
if (BUILD_TESTING)
    add_subdirectory(test)
endif()
