project(fire_engine)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

set(Boost_USE_STATIC_LIBS OFF)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(fire_engine_test unit_test.cpp)
target_link_libraries(fire_engine_test fire_engine ${Boost_LIBRARIES})
