cmake_minimum_required(VERSION 3.28)
project(
    Assembler
    VERSION 1.0
    DESCRIPTION "A limit order book system written in C++"
    LANGUAGES CXX
)

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Assembler)

target_sources(
    Assembler
    PRIVATE
    ./src/main.cpp
)
