CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
project(srpg_engine)

# Loading SDL.
find_package(SDL2 COMPONENTS graphics window REQUIRED)
find_package(SDL2_image REQUIRED)

# Maybe add header files, though that shouldn't be needed.
add_library(srpg_engine unit.cc weapon.cc unit_attrs.hh unit_attrs.cc combat.cc combat.hh map.cc graphics.hh graphics.cc error.hh error.cc random.hh random.cc)
target_link_libraries(srpg_engine ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
include_directories(${SDL2_INCLUDE_DIRS})
add_executable(main main.cc)
target_link_libraries(main srpg_engine)