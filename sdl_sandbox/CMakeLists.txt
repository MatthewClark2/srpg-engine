# Loading SDL.
find_package(SDL2 REQUIRED)

# Maybe add header files, though that shouldn't be needed.
include_directories(${SDL2_INCLUDE_DIRS})
add_executable(sdlmain main.cpp exercise1.cpp)
target_link_libraries(sdlmain ${SDL2_LIBRARIES})