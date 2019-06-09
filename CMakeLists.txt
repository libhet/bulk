cmake_minimum_required(VERSION 3.14)
project(bulk)

set(CMAKE_CXX_STANDARD 14)

add_executable(${PROJECT_NAME}
        src/main.cpp
        src/bulk.cpp
        src/bulk.h
        src/observer.cpp
        src/observer.h
        src/command.cpp
        src/command.h
        src/Bulk_Observer.cpp
        src/Bulk_Observer.h
        src/Bulk_CommandReader.cpp
        src/Bulk_CommandReader.h)

add_subdirectory(tests)