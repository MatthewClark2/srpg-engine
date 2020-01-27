CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
project(srpg_engine)

# Maybe add header files, though that shouldn't be needed.
add_library(srpg_engine unit.cpp weapon.cpp unit_attrs.h)
add_executable(main main.cpp)
target_link_libraries(main srpg_engine)