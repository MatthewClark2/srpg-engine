cmake_minimum_required(VERSION 3.10)
project(srpg_engine)

set(CMAKE_CXX_STANDARD 17)

option(TEST_SDL OFF)

if(${TEST_SDL})
    add_subdirectory(sdl_sandbox)
endif()

add_subdirectory(src)
include_directories(src)

# This is commented out since I can't make CLion play nice. Unfortunately, this means all of the tests need to be
# compiled at every build.
# option(testing "Build unit tests." ON)
# if(testing)
add_subdirectory(test)
# endif()