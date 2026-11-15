cmake_minimum_required(VERSION 4.4.0)

project(Assembler)

add_executable(Assembler)

target_sources(
    Assembler
    PRIVATE
    ./main.cpp
)
