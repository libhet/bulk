cmake_minimum_required(VERSION 3.14)
project(bulk)

set(CMAKE_CXX_STANDARD 14)

add_executable(${PROJECT_NAME}
        src/main.cpp
        src/Bulk_Observer.cpp
        src/Bulk_Observer.h
        src/Bulk_CommandReader.cpp
        src/Bulk_CommandReader.h src/Bulk_Console.h src/Bulk_FileLoger.h src/PrettyPrinter.h)

add_subdirectory(tests)