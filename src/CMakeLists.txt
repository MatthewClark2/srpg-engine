CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
project(fire_engine)

# Maybe add header files, though that shouldn't be needed.
add_library(fire_engine unit.cpp weapon.cpp)
add_executable(main main.cpp)
target_link_libraries(main fire_engine)