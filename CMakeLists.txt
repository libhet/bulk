cmake_minimum_required(VERSION 3.14)
project(bulk)

set(CMAKE_CXX_STANDARD 14)

add_executable(${PROJECT_NAME}
        src/main.cpp
        src/bulk.cpp
        src/bulk.h )

add_subdirectory(tests)