cmake_minimum_required(VERSION 3.10)
project(fire_engine)

set(CMAKE_CXX_STANDARD 17)

option(testing "Build unit tests." OFF)

add_subdirectory(src)
include_directories(src)

if(testing)

    find_package(Boost COMPONENTS unit_test_framework REQUIRED)
    add_subdirectory(test)
endif()