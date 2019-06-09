cmake_minimum_required(VERSION 3.5)

enable_testing()
include(CTest)

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

project(bulk_test)

add_executable(${PROJECT_NAME}
        main_test.cpp
        bulk_test.cpp command_test.cpp)

set_target_properties(${PROJECT_NAME} PROPERTIES
        CMAKE_CXX_STANDARD 14
        CMAKE_CXX_STANDARD_REQUIRED ON
        INCLUDE_DIRECTORIES ${GTEST_INCLUDE_DIRS}
        )

target_link_libraries(${PROJECT_NAME} GTest::GTest Threads::Threads)

add_test(${PROJECT_NAME} ${PROJECT_NAME})