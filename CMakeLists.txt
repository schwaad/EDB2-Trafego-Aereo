
cmake_minimum_required(VERSION 3.10)

project(EDB2TrafegoAereo)

include_directories(include)

file(GLOB SOURCES "src/*.c")
add_executable(EDB2TrafegoAereo ${SOURCES})

set(CMAKE_C_STANDARD 99)

