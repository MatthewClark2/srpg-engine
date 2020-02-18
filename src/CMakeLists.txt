CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
project(srpg_engine)

# Loading SDL.
find_package(SDL2 COMPONENTS graphics window REQUIRED)

# Maybe add header files, though that shouldn't be needed.
add_library(srpg_engine unit.cpp weapon.cpp unit_attrs.h unit_attrs.cpp combat.cpp combat.h map.cpp)
target_link_libraries(srpg_engine ${SDL2_LIBRARY})
include_directories(${SDL2_INCLUDE_DIRECTORIES})
add_executable(main main.cpp)
target_link_libraries(main srpg_engine)